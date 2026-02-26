#include <stdio.h>
#include <stdlib.h>

#include "../include/constants.h"
#include "../include/error_messages.h"
#include "../include/stack.h"

typedef struct Stack Stack;

Stack *stack_init(void) {
        Stack *self = (Stack *) malloc(sizeof(Stack));

        if (self == NULL) {
                fprintf(stderr, ERR_STACK_INIT_FAILURE);
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
                fprintf(stderr, ERR_STACK_OVERFLOW);
                return -1;
        }

        self->top++;
        self->stack[self->top] = data;
        return 0;
}

int stack_pop(Stack *self) {
        if (stack_empty(self) == 1) {
                fprintf(stderr, ERR_STACK_UNDERFLOW);
                return -1;
        }

        self->top--;
        return self->stack[self->top + 1];
}