#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include "constants.h"
#include "error_messages.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int memory_allocation_check(void *ptr) {
        if (ptr == NULL) {
                fprintf(stderr, ERR_MEMORY_ALLOC_FAIL);
                return 1;
        }
        else return 0;
}

void free_memory(void *ptr, ...) {
        va_list args;
        va_start(args, ptr);
        while (ptr != NULL) {
                free(ptr);
                ptr = va_arg(args, void *);
        }
        va_end(args);
}

#endif