#include <stdio.h>

#include "../include/error_messages.h"
#include "../include/input_validation.h"

int extension_checker(const char *filename) {
        while (*filename != '\0') {
                if (*filename != '.') {
                        filename++;
                        continue;
                }
                
                if (*(filename + 1) == '\0' || *(filename + 2) == '\0') return 0;
                // Short circuit evaluation makes this code memory safe
                
                else if (*(filename + 1) == 'b' &&
                         *(filename + 2) == 'f' &&
                         *(filename + 3) == '\0') return 1;

                else filename++;
        }
        return 0;
}

int validate_number_of_arguments(const int num_args, const char* binary_name) {
        if (num_args < 2) {
                fprintf(stderr, ERR_NUMBER_OF_ARGS, binary_name);
                return 1;
        }
        else {
                return 0;
        }
}

int validate_file_extension(const char *filename) {
        if (extension_checker(filename) == 0) {
                fprintf(stderr, ERR_WRONG_FILE_EXTENSION, filename);
                return 1;
        }
        else {
                return 0;
        }
}

int validate_file_exists(FILE *file_ptr, const char *filename) {
        if (file_ptr == NULL) {
                perror(filename);
                return 1;
        }
        else return 0;
}

int validate_file_not_empty(FILE **file_ptr, int file_character) {
        if (file_character == EOF) {
                fprintf(stderr, ERR_EMPTY_FILE);
                fclose(*file_ptr);
                return 1;
        }
        else rewind(*file_ptr);
        return 0;
}