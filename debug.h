#ifndef DEBUG_H
#define DENUG_h

#include <stdio.h>
#include <stdarg.h>

#ifdef DEBUG
    #define INFO(...) printf(__VA_ARGS__)
#else
    #define INFO(...) ;
#endif

#endif