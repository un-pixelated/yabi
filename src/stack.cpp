#include <iostream>
#include <cstdlib>

#include "../include/constants.h"
#include "../include/error_messages.h"

class Stack {
public:
    int top;
    int stack[STACK_SIZE];
};

// Same functions, just using class instead of struct

Stack *stack_init(void) {
    Stack *self = (Stack *) std::malloc(sizeof(Stack));

    if (self == NULL) {
        std::cerr << ERR_STACK_INIT_FAILURE;
        return NULL;
    }

    self->top = -1;
    return self;
}

int stack_empty(Stack *self) {
    if (self->top == -1) return 1;
    return 0;
}

int stack_full(Stack *self) {
    if (self->top == STACK_SIZE - 1) return 1;
    return 0;
}

int stack_push(Stack *self, int data) {
    if (stack_full(self) == 1) {
        std::cerr << ERR_STACK_OVERFLOW;
        return -1;
    }

    self->top++;
    self->stack[self->top] = data;
    return 0;
}

int stack_pop(Stack *self) {
    if (stack_empty(self) == 1) {
        std::cerr << ERR_STACK_UNDERFLOW;
        return -1;
    }

    self->top--;
    return self->stack[self->top + 1];
}