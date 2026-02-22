#include <stdio.h>

int main(int argc, char *argv[]) {
        if (argc < 2) {
                fprintf(stderr, "usage: %s file.bf\n", argv[0]);
                return 1;
        }

        // TODO: Add .bf validation

        FILE *brainfuck_file_pointer = fopen(argv[1], "r");
        if (brainfuck_file_pointer == NULL) {
                perror(argv[1]);
                return 1;
        }

        int current_character;
        while ((current_character = fgetc(brainfuck_file_pointer)) != EOF) {
                // interpreter implementation goes here.
                // we're simulating BF as we read the file
                // Pros: faster, more memory efficient
                // Cons: doesn't catch errors like mismatched parentheses

        }

        fclose(brainfuck_file_pointer);
        return 0;
}