#include "uriparser.h"
#include "logging.h"
#include "macroutils.h"

#include <arpa/inet.h>

#include <limits.h>
#include <string.h>

#define PCRE2_CODE_UNIT_WIDTH CHAR_BIT
#include <pcre2.h>  // pkg-config --cflags --libs libpcre2-8

static const char *const c_p_uri = (
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
    
    while (NULL != groupnames)
}
