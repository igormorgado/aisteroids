#ifndef __DEBUG_H__
#define __DEBUG_H__
/*
 * TODO:
 * Add level to debug
 * Add timestamp to debug
 */
// debug_print_body_fmt(body) do { char *s= ...; debug_print("%s", s); free(s); } while(0)

#include <stdio.h>

enum LOGLEVEL
{
    LL_EMERG = 0,
    LL_ALERT,
    LL_CRIT,
    LL_ERR,
    LL_WARN,
    LL_NOTICE,
    LL_INFO,
    LL_DEBUG
};


#define debug_print(fmt, ...) do { if (DEBUG) fprintf(stderr, "%s:%d:%s() " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__); } while(0)

#endif /* __DEBUG_H__ */
