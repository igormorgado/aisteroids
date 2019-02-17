#ifndef __DEBUG_H__
#define __DEBUG_H__
/*
 * TODO:
 * Add level to debug
 * Add timestamp to debug
 */

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

#ifdef DEBUG
#define debug_flags 1
#else
#define debug_flags 0
#endif
	

#define debug_print(fmt, ...)					\
	do {							\
		if(debug_flags) {				\
			fprintf(stderr, "%s:%d:%s() " fmt,     	\
					__FILE__,	       	\
					__LINE__,	       	\
					__func__,	       	\
					__VA_ARGS__);	       	\
		}						\
	} while(0)						\

#define debug_print_gameobj_fmt(obj)				\
	do {							\
		if(debug_flags) {				\
		char *s = gameobj__fmt(obj);			\
		debug_print("%s\n", s);				\
		free(s);					\
		s = NULL;					\
		}						\
	} while(0)						\

#define debug_print_ship_fmt(ship)				\
	do {							\
		if(debug_flags) {				\
		char *s = ship__fmt(ship);			\
		debug_print("%s\n", s);				\
		free(s);					\
		s = NULL;					\
		}						\
	} while(0)						\

#endif /* __DEBUG_H__ */
