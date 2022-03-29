#include "uriparser.h"
#include "logging.h"
#include "macroutils.h"

#include <arpa/inet.h>

#include <limits.h>
#include <string.h>
#include <stdio.h>

#define PCRE2_CODE_UNIT_WIDTH CHAR_BIT
#include <pcre2.h>  // pkg-config --cflags --libs libpcre2-8

static const char *const uri_re = (
    "^ (?P<proto> tcp|udp|unix) : \\/\\/ (?: " // именованная группа содержащая tcp или udp или unix, ':', '//', начало группы ip + домен или пути
    "  (?: "                                   // группа ip + домен
    "    (?P<ip> "                             // именованная группа ip
    "        \\d{1,3} (?: \\.\\d{1,3}) {3} "   // 1 - 3 цифры за которыми следует еще 3 группы повторяющихся 1 - 3 цифр с префиксом '.'
    "    ) | (?P<host> "                       // именованная группа домена
    "      (?: [a-zA-Z0-9] | [a-zA-Z0-9][a-zA-Z0-9\\-]{0,61} [a-zA-Z0-9]) "
    "      (?: \\. (?: [a-zA-Z0-9] | [a-zA-Z0-9][a-zA-Z0-9\\-]{0,61} [a-zA-Z0-9])) *"
    "    ) "                                   // конец группы ip + домен
    "    : (?P<port> \\d{1,6}) "               // ':', установка порта размером 1 - 6 цифр 
    "  ) | (?P<path> "                         // или именованная группа домена вместо группы ip + домен
    "     [^[:cntrl:]] + "                     // содержит всё кроме контрольного символа повторяющегося более одного раза
    "  ) "                                     // конец группы пути
    ")$"                                       // конец файла
);

// группы
static const char *uri_groupnames[] = {"proto", "ip", "host", "port", "path", NULL};

static long re_collect_named(const char *regex, const char *string,
	                         const char **groupnames, char **collected)
{
	if (NULL == regex || NULL == string || 
		NULL == groupnames || NULL == collected) {
		return RE_WRONG_ARGS;
	}

	long ngroups = 0;
    

    // 1. цикл может оказаться бесконечным, это плохая практика, нужен счетчик максимального количества итераций.
    // 2. идет расчет размера нультерминированного массива
    while (NULL != groupnames[ngroups]) {
        ngroups++;
    }

    log_info("Detected %ld groups", ngroups);
   
    int re_err = 0;

    PCRE2_SIZE _re_errorffset;
    
    // собирает regexp в "некий байткод" для дальнейшей работы с ним
    // _re_errorffset - позиция в regex  где ошибка
    pcre2_code *re = pcre2_compile((PCRE2_SPTR)regex, PCRE2_ZERO_TERMINATED, PCRE2_EXTENDED | PCRE2_UTF,
                                  &re_err, &_re_errorffset, NULL);

    // если pcre2_compile возвращает NULL, те ошибку
    if (NULL == re) {
        char buffer[100];
        
        // вставит в buffer ообщение от ошибке
        pcre2_get_error_message(re_err, (unsigned char *)buffer, arr_len(buffer));
        log_crit("Regexp compilation error %d @ %llu : %s", re_err, (long long unsigned)_re_errorffset, buffer);

        return RE_WRONG_PATTERN;
    }

    log_info("Regexp compiled");

    int ret = 0;

    // алоцирует память для работы с regex по результатом компилировния regex
    pcre2_match_data *match = pcre2_match_data_create_from_pattern(re, NULL);

    if (NULL == match) {
        log_crit("Match block could not be obtained");

        ret = RE_RESOURCE_ERROR;
        goto code_free;
    }

    // проверяет переданную строку с переаднным regex
    // (PCRE2_SIZE)0 - смещение в regex откуда начинать проверять 
    // возвращает количество групп или -1
    long mcnt = pcre2_match(re, (PCRE2_SPTR) string, (PCRE2_SIZE)strlen(string),(PCRE2_SIZE)0, 0, match, NULL);

    if (mcnt < 1) {
        log_err("No matches. Match count is %ld", mcnt);
        ret = RE_NOMATCH;

        goto match_free;
    }

    log_info("Match count %ld", mcnt);
    
    // просто посмотреть результат совподений по группам из pcre2_match()
    if (DEBUG >= 4) {
        PCRE2_SIZE *ovector = pcre2_get_ovector_pointer(match);

        for (long i = 0; i < mcnt; i++) {
            PCRE2_SPTR substring_start = string + ovector[2*i];
            PCRE2_SIZE substring_length = ovector[2*i + 1] - ovector[2*i];

            log_info(" Item %2ld: %.*s", i, (int)substring_length, (char *)substring_start);
        }
    }

    log_info("Trying to extract %ld fields", (long)ngroups);
    long numfound = 0;
    
    for (long i = 0; i < ngroups; i++) {
        char *val = NULL;
        PCRE2_SIZE len = 0;

        long err = pcre2_substring_get_byname(match, (PCRE2_SPTR)(groupnames[i]), (PCRE2_UCHAR **)&val, &len);

        switch (err) {
            case 0:
                break;
            case PCRE2_ERROR_UNSET:
                log_warn("PCRE group %ld (\"%s\" value not found", (long)i, groupnames[i]);
                collected[i] = NULL;
                continue;
            default:
                log_warn("PCRE group get for field %s returned %ld", groupnames[i], err);
                collected[i] = NULL;
                continue;
        }

        log_info(" Found %s=%s", groupnames[i], val);

        numfound++;

        // алоцируется и сохраняется результат
        collected[i] = strdup(val);

        if (NULL == collected[i]) {
            log_crit("Could not allocate memory for storing result %ld", (long)i);
            ret = RE_RESOURCE_ERROR;

            for (long k = i - 1; k >= 0; k--) {
                free(collected[k]);
                log_warn("Freeing %ld '%s'", (long)k, collected[k]);
            }

            goto match_free;
        }
    }

    log_info("Filled %ld matched groups", numfound);
    ret = numfound;

    match_free:
        log_info("Deallocating re match data");
        pcre2_match_data_free(match);
    code_free:
        log_info("Deallocating re compiled code");
        pcre2_code_free(re);

    return ret;
}

bool uri_parse(const char *uristring, struct socket_uri *resuri)
{
    if (NULL == resuri || NULL == uristring) {
        return false;
    }

    char *groupvals[arr_len(uri_groupnames) - 1];
    long found = re_collect_named(uri_re, uristring, uri_groupnames, groupvals);

    if (found < 1) {
        return false;
    }

    const char *proto = groupvals[0],
               *ip = groupvals[1],
               *host = groupvals[2],
               *port = groupvals[3],
               *path = groupvals[4];

    log_info("HOST: %s IP: %s", host, ip);

    struct socket_uri res = {
        .type = (!strcmp(proto, "tcp") ? STYPE_TCP : !strcmp(proto, "udp") ? STYPE_UDP : STYPE_UNIX)
    };

    if (STYPE_UNIX != res.type) {
        long long p;

        if (NULL == port || sscanf(port, "%lld", &p) < 1 || p > 65535) {
            log_err("port conversation failed");
            return false;
        }

        res.port = htons(p);
    }

    if (NULL != path) {
        res.path = strdup(path);

        if (NULL == res.path) {
            log_err("path memory allocation failed");
            return false;
        }
    } else if ((NULL != ip) && (NULL == host)) {
        if (!inet_aton(ip, &res.ip)) {
            log_err("ip/port conversation failed");
            return false;
        }
        res.host = NULL; 
    } else {
        log_crit("Unexpected uri combination");
        return false;
    }

    log_info("Freeing intermediate groupvals");
    arr_foreach(v, groupvals) {
        log_info("  %s", v);
        free(v);
    }

    memcpy(resuri, &res, sizeof(res));

    return true;
}
