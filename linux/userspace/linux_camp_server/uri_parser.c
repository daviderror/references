#include <arpa/inet.h>
#include <limits.h>
#include <string.h>

#include "uri_parser.h"
#include "logging.h"
#include "macroutils.h"

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

static const char *uri_group_names[] = {"proto", "ip", "host", "port", "path", NULL};

static long re_collect_named(const char *regex, const char *string,
	                         const char **group_names, char **collected)
{
	if (NULL == regex || NULL == string || 
		NULL == group_names || NULL == collected) {
		return -1L;
	}

	
}
