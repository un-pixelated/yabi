#ifndef CONSTANTS_H
#define CONSTANTS_H

/*
The constants header defines constants which might be re-used multiple times
in the interpreter and elsewhere so it's good to have them all in one place.
*/

// I want this modifiable by the user input flags
#define ARRAY_LENGTH 30000;

// size in bytes, ideally 7 bits (< 1 byte) to support ASCII for now we go with 1
#define CELL_SIZE 1;

// size for the parentheses matching stack, also changable for your program needs
// why 1024? God help you if you're writing a brainfuck program with more nesting depth than this.
#define STACK_SIZE 1024;

#endif