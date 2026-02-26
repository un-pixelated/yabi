#ifndef BUILD_BRACKET_MAP_H
#define BUILD_BRACKET_MAP_H

#include <stdio.h>

#include "stack.h"
#include "error_messages.h"

int build_bracket_map(FILE *bf_fileptr, int *bracket_map, Stack *validation_stack);

#endif