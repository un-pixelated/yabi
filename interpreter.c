#include <stdio.h>
#include <stdlib.h>

#include "./include/constants.h"
#include "./include/input_validation.h"
#include "./include/memory_management.h"
#include "./include/pass_one.h"
#include "./include/pass_two.h"

int main(int argc, char *argv[]) {
        if (validate_number_of_arguments(argc, argv[0]) == 1) return 1;
        
        char *filename = argv[1];

        if (validate_file_extension(filename) == 1) return 1;

        FILE *bf_fileptr = fopen(filename, "r");
        if (validate_file_exists(bf_fileptr, filename) == 1) return 1;

        if (validate_file_not_empty(&bf_fileptr, fgetc(bf_fileptr)) == 1) return 1;

        // bracket_map[position of opening bracket] = position of closing bracket
        // bracket_map[position of closing bracket] = position of opening bracket
        int *bracket_map = malloc(MAP_LEN * sizeof(int));
        if (memory_allocation_check(bracket_map) == 1) {
                fclose(bf_fileptr);
                return 1;
        }

        Stack *validation_stack = stack_init();
        if (memory_allocation_check(validation_stack) == 1) {
                free_memory(bracket_map, NULL);
                fclose(bf_fileptr);
                return 1;
        }

        // pass 1
        if (build_bracket_map(bf_fileptr, bracket_map, validation_stack) == 1) {
                free_memory(bracket_map, validation_stack, NULL);
                fclose(bf_fileptr);
                return 1;
        }
        free_memory(validation_stack, NULL);

        char *cell_array = calloc(CELL_ARRAY_LENGTH, CELL_SIZE);
        if (memory_allocation_check(cell_array) == 1) {
                free_memory(bracket_map, NULL);
                fclose(bf_fileptr);
                return 1;
        }

        // pass 2
        rewind(bf_fileptr);
        interpret_bf(bf_fileptr, bracket_map, cell_array);

        free_memory(bracket_map, cell_array, NULL);
        fclose(bf_fileptr);
        return 0;
}