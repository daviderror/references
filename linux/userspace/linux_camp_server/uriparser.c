#include "uriparser.h"
#include "logging.h"
#include "macroutils.h"

#include <arpa/inet.h>

#include <limits.h>
#include <string.h>

#define PCRE2_CODE_UNIT_WIDTH CHAR_BIT
#include <pcre2.h>  // pkg-config --cflags --libs libpcre2-8

static const char *const uri = (
    "^ (?P<proto> tcp|udp|unix) : \\/\\/ (?: "
    "  (?: "
    "    (?P<ip> "
    "        \\d{1,3} (?: \\.\\d{1,3}) {3} "
    "    ) | (?P<host> "
    "      (?: [a-zA-Z0-9] | [a-zA-Z0-9][a-zA-Z0-9\\-]{0,61} [a-zA-Z0-9]) "
    "      (?: \\. (?: [a-zA-Z0-9] | [a-zA-Z0-9][a-zA-Z0-9\\-]{0,61} [a-zA-Z0-9])) *"
    "    ) "
    "    : (?P<port> \\d{1,6})"
    "  ) | (?P<path> "
    "     [^[:cntrl:]] + "
    "  ) "
    ")$"
);

static const char *uri_groupnames[] = {"proto", "ip", "host", "port", "path", NULL};

static long re_collect_named(const char *regex, const char *string,
	                         const char **groupnames, char **collected)
{
	if (NULL == regex || NULL == string || 
		NULL == groupnames || NULL == collected) {
		return RE_WRONG_ARGS;
	}

	long ngroups = 0;
    

    // цикл может оказаться бесконечным, это плохая практика, нужен счетчик максимального количества итераций.
    while (NULL != groupnames[ngroups]) {
        ngroups++;
    }

    log_info("Detected %ld groups", ngroups);
    
    int re_err = 0;

    PCRE2_SIZE _re_errorffset;

    pcre2_code *re = pcre2_compile((PCRE2_SPTR)regexp, PCRE2_ZERO_TERMENATED, PCRE2_EXTENDED | PCRE2_UTF,
                                  &re_err, &_re_errorffset, NULL);

    if (NULL == re) {
        char buffer[100];

        pcre_get_error_message(re_err, (unsigned char *)buffer, arr_len(buffer));
        log_crit("Regexp compilation error %d @ %llu : %s", re_err, (long long unsigned)_re_errorffset, buffer);

        return RE_WRONG_PATTERN;
    }

    log_info("Regexp compiled");

    int ret = 0;

    pcre2_match_data *match = pcre2_match_create_from_pattern(re, NULL);

    if (NULL == match) {
        log_crit("Match block could not be obtained");

        ret = RE_RESOURCE_ERROR;
        goto code_free;
    }

    long mcnt = pcre2_match(re, (PCRE2_SPTR) string, (PCRE2_SIZE)strlen(string),(PCRE2_SIZE)0, 0, match, NULL);

    if (mcnt < 1) {
        log_err("No matches. Match count is %ld", mcnt);
        ret = RE_NOMATCH;

        goto match_free;
    }

    log_info("Match count %ld", mcnt);

    if (DEBUG >= LOG_INFO) {
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
        pce2_code_free(re);

    return ret;
}

bool uri_parse(const char *uristring, struct socket_uri *result)
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
        .type = (!strcmp(proto, "tcp") ? STYLE_TCP : !strcmp(proto, "udp") ? STYLE_UDP : STYLE_UNIX);
    };

    if (STYLE_UNIX != res.type) {
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
            log.err("path memory allocation failed");
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