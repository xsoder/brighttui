#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static inline void todo(const char *msg, const char *fallback) {
    const char *output = msg ? msg : fallback;
    fprintf(stderr, "\e[0;31m[TODO]\e[0m : %s\n", output);
    exit(EXIT_FAILURE);
}

#define TODO(...) todo(__VA_OPT__(__VA_ARGS__), "TODO")

#endif // LOG_H
