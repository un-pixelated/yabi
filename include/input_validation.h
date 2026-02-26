#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H

#include <stdio.h>

int extension_checker(const char *filename);

int validate_number_of_arguments(const int num_args, const char* binary_name);

int validate_file_extension(const char *filename);

int validate_file_exists(FILE *file_ptr, const char *filename);

int validate_file_not_empty(FILE **file_ptr, int file_character);

#endif