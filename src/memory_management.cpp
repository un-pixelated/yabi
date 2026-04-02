#include <iostream>
#include <cstdarg>
#include <cstdlib>

#include "../include/error_messages.h"
#include "../include/memory_management.h"

int memory_allocation_check(void* ptr) {
    if (ptr == nullptr) {
        std::cerr << ERR_MEMORY_ALLOC_FAIL;
        return 1;
    }
    return 0;
}

void free_memory(void* ptr, ...) {
    va_list args;
    va_start(args, ptr);

    while (ptr != nullptr) {
        std::free(ptr);
        ptr = va_arg(args, void*);
    }

    va_end(args);
}