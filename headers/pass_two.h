#ifndef PASS_TWO_H
#define PASS_TWO_H

#include <stdio.h>

#include "constants.h"

void interpret_brainfuck(FILE *bf_fileptr, char *cell_array, int *bracket_map) {
        
        int cell_ptr = 0;
        int curr_char = 0;
        int char_idx = 0;

        while ((curr_char = fgetc(bf_fileptr)) != EOF) {
                switch (curr_char) {
                        case '>':
                        // wraparound
                        if (cell_ptr == CELL_ARRAY_LENGTH - 1) {
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
                                cell_ptr = CELL_ARRAY_LENGTH - 1;
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
}

#endif