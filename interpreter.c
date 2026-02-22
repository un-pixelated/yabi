#include <stdio.h>
#include <stdlib.h>

#include "./headers/constants.h"
#include "./headers/helpers.h"
#include "./headers/stack.h"

int main(int argc, char *argv[]) {
        if (argc < 2) {
                fprintf(stderr, "usage: %s file.bf\n", argv[0]);
                return 1;
        }

        if (validate_ext(argv[1]) == 0) {
                fprintf(stderr, "%s is not a valid brainfuck file\nfile extension must be .bf\n", argv[1]);
                return 1;
        }

        FILE *bf_fileptr = fopen(argv[1], "r");
        if (bf_fileptr == NULL) {
                perror(argv[1]);
                return 1;
        }

        char *cell_array = calloc(ARRAY_LENGTH, CELL_SIZE);
        if (cell_array == NULL) {
                fprintf(stderr, "couldn't allocate memory\n");
                return 1;
        }

        int curr_char;

        int char_idx = 0;
        
        // bracket_map[position of opening bracket] = position of closing bracket
        // bracket_map[ '[' ] = ']' (but int positions)
        int bracket_map[ARRAY_LENGTH];

        Stack *validation_stack = stack_init();
        if (validation_stack == NULL) {
                return 1;
        }

        while ((curr_char = fgetc(bf_fileptr)) != EOF) {
                if (curr_char != '[' && curr_char != ']') {
                        char_idx++;
                        continue;
                }
                
                else if (curr_char == '[') {
                        stack_push(validation_stack, char_idx);
                        char_idx++;
                }

                else {
                        int closer_position = stack_pop(validation_stack);
                        if (closer_position == -1) {
                                return 1;
                        }

                        bracket_map[closer_position] = char_idx;
                        char_idx++;
                }
        }

        fclose(bf_fileptr);
        return 0;
}