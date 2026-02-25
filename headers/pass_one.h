#ifndef BUILD_BRACKET_MAP_H
#define BUILD_BRACKET_MAP_H

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "error_messages.h"
#include "memory_management.h"

int build_bracket_map(int *bracket_map, Stack *validation_stack, FILE *bf_fileptr) {

        int curr_char;
        int char_idx = 0;

        while ((curr_char = fgetc(bf_fileptr)) != EOF) {
                if (curr_char != '[' && curr_char != ']') {
                        char_idx++;
                        continue;
                }
                
                else if (curr_char == '[') {
                        int push = stack_push(validation_stack, char_idx);
                        if (push == -1) {
                                return 1;
                        }
                        char_idx++;
                }

                else {
                        int closer_position = stack_pop(validation_stack);
                        if (closer_position == -1) {
                                return 1;
                        }

                        bracket_map[closer_position] = char_idx;
                        bracket_map[char_idx] = closer_position;
                        char_idx++;
                }
        }

        if (stack_empty(validation_stack) == 0) {
                fprintf(stderr, ERR_BRACKET_MISMATCH);
                return 1;
        }

        return 0;
}

#endif