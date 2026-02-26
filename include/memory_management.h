#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "error_messages.h"

int memory_allocation_check(void *ptr);

void free_memory(void *ptr, ...);

#endif