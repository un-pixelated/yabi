#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

struct Stack {
        int stack[STACK_SIZE];
        int top;
};

typedef struct Stack Stack;

Stack *stack_init(void) {
        Stack *self = (Stack *) malloc(sizeof(Stack));

        if (self == NULL) {
                fprintf(stderr, "error: couldn't initialize stack\n");
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
                fprintf(stderr, "error: stack overflow\n");
                return -1;
        }

        self->top++;
        self->stack[self->top] = data;
        return 0;
}

int stack_pop(Stack *self) {
        if (stack_empty(self) == 1) {
                fprintf(stderr, "error: stack underflow\n");
                return -1;
        }

        self->top--;
        return self->stack[self->top + 1];
}

#endif