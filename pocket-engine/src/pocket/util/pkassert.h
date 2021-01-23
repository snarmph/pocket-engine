#ifndef PKASSERT_H
#define PKASSERT_H

#include <stdio.h>
#include <stdlib.h>

#ifdef NDEBUG
#define pkassert(condition, msg) 0
#else
#define pkerror(condition, file, line, msg) printf("condition: [" condition "] failed at " file ":%d, message: " msg "\n", line)
#define pkassert(condition, msg)                            \
            if(!(condition)) {                              \
            pkerror(#condition, __FILE__, __LINE__, msg);   \
            exit(0);                                        \
        }

#endif

#endif