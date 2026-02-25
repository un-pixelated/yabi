#include <stdio.h>
#include <stdlib.h>

#include "./headers/constants.h"
#include "./headers/input_validation.h"
#include "./headers/stack.h"
#include "./headers/memory_management.h"

int main(int argc, char *argv[]) {
        if (validate_number_of_arguments(argc, argv[0]) == 1) return 1;
        
        char *filename = argv[1];

        if (validate_file_extension(filename) == 1) return 1;

        FILE *bf_fileptr = fopen(filename, "r");
        if (validate_file_exists(bf_fileptr, filename) == 1) return 1;

        if (validate_file_not_empty(&bf_fileptr, fgetc(bf_fileptr)) == 1) return 1;

        char *cell_array = calloc(ARRAY_LENGTH, CELL_SIZE);
        if (memory_allocation_check(cell_array) == 1) return 1;

        int curr_char;
        int char_idx = 0;
        
        // bracket_map[position of opening bracket] = position of closing bracket
        // bracket_map[position of closing bracket] = position of opening bracket
        int bracket_map[MAP_LEN];

        Stack *validation_stack = stack_init();
        if (memory_allocation_check(validation_stack) == 1) return 1;

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
        
        int cell_ptr = 0;
        char_idx = 0;

        while ((curr_char = fgetc(bf_fileptr)) != EOF) {
                switch (curr_char) {
                        case '>':
                        // wraparound
                        if (cell_ptr == ARRAY_LENGTH - 1) {
                                cell_ptr = 0;
                                char_idx++;
                                break;
                        }
                        cell_ptr++;
                        char_idx++;
                        break;

                        case '<':
                        // wraparound
                        if (cell_ptr == 0) {
                                cell_ptr = ARRAY_LENGTH - 1;
                                char_idx++;
                                break;
                        }
                        cell_ptr--;
                        char_idx++;
                        break;

                        case '+':
                        cell_array[cell_ptr]++;
                        // cell wraparound
                        if (cell_array[cell_ptr] == -128) cell_array[cell_ptr] = 0;
                        char_idx++;
                        break;

                        case '-':
                        cell_array[cell_ptr]--;
                        // cell wraparound
                        if (cell_array[cell_ptr] == -1) cell_array[cell_ptr] = 127;
                        char_idx++;
                        break;

                        case '.':
                        printf("%c", cell_array[cell_ptr]);
                        char_idx++;
                        break;

                        case ',':
                        scanf("%c", &cell_array[cell_ptr]);
                        char_idx++;
                        break;
                        
                        case '[':
                        if (cell_array[cell_ptr] == 0) {
                                char_idx = bracket_map[char_idx] + 1;
                                fseek(bf_fileptr, char_idx, SEEK_SET);
                        }
                        else char_idx++;
                        break;

                        case ']':
                        if (cell_array[cell_ptr] != 0) {
                                char_idx = bracket_map[char_idx] + 1;
                                fseek(bf_fileptr, char_idx, SEEK_SET);
                        }
                        else char_idx++;
                        break;

                        default:
                        // handling comments
                        char_idx++;
                        break;
                }
        }
        printf("\n"); 

        free(cell_array);
        fclose(bf_fileptr);
        return 0;
}