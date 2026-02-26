#ifndef ERROR_MESSAGES_H
#define ERROR_MESSAGES_H

#define ERR_NUMBER_OF_ARGS "usage: %s file.bf\n"
#define ERR_WRONG_FILE_EXTENSION "error: %s is not a valid brainfuck file\n       file extension must be .bf\n"
#define ERR_EMPTY_FILE "error: empty file\n"

#define ERR_MEMORY_ALLOC_FAIL "error: couldn't allocate memory\n"

#define ERR_STACK_INIT_FAILURE "error: couldn't initialize stack\n"
#define ERR_STACK_OVERFLOW "error: stack overflow\n"
#define ERR_STACK_UNDERFLOW "error: stack underflow\n"

#define ERR_BRACKET_MISMATCH "error: bracket mismatch\n"


#endif