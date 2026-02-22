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
        // bracket_map[position of closing bracket] = position of opening bracket
        // bracket_map[ '[' ] = ']' (but int positions)
        // bracket_map[ ']' ] = '[' (but int positions)
        int bracket_map[ARRAY_LENGTH];

        Stack *validation_stack = stack_init();
        if (validation_stack == NULL) {
                free(cell_array);
                return 1;
        }

        // pass 1
        while ((curr_char = fgetc(bf_fileptr)) != EOF) {
                if (curr_char != '[' && curr_char != ']') {
                        char_idx++;
                        continue;
                }
                
                else if (curr_char == '[') {
                        int push = stack_push(validation_stack, char_idx);
                        if (push == -1) {
                                free(validation_stack);
                                free(cell_array);
                                return 1;
                        }
                        char_idx++;
                }

                else {
                        int closer_position = stack_pop(validation_stack);
                        if (closer_position == -1) {
                                free(validation_stack);
                                free(cell_array);
                                return 1;
                        }

                        bracket_map[closer_position] = char_idx;
                        bracket_map[char_idx] = closer_position;
                        char_idx++;
                }
        }

        if (stack_empty(validation_stack) == 0) {
                fprintf(stderr, "bracket mismatch\n");
                free(validation_stack);
                free(cell_array);
                return 1;
        }

        free(validation_stack);

        // pass 2
        rewind(bf_fileptr);
        
        char_idx = 0;

        while ((curr_char = fgetc(bf_fileptr)) != EOF) {
                switch (curr_char) {
                        case '>':
                        // wraparound
                        if (char_idx == ARRAY_LENGTH - 1) {
                                char_idx = 0;
                                break;
                        }
                        char_idx++;
                        break;

                        case '<':
                        // wraparound
                        if (char_idx == 0) {
                                char_idx = ARRAY_LENGTH - 1;
                                break;
                        }
                        char_idx--;
                        break;

                        case '+':
                        cell_array[char_idx]++;
                        // cell wraparound
                        if (cell_array[char_idx] == -128) cell_array[char_idx] = 0;
                        break;

                        case '-':
                        cell_array[char_idx]--;
                        // cell wraparound
                        if (cell_array[char_idx] == -1) cell_array[char_idx] = 127;
                        break;

                        case '.':
                        printf("%c", cell_array[char_idx]);
                        break;

                        case ',':
                        scanf("%c", &cell_array[char_idx]);
                        break;

                        // TODO LOOPS

                        default:
                        // handling comments
                        break;
                }
        }
        printf("\n"); 

        free(cell_array);
        fclose(bf_fileptr);
        return 0;
}