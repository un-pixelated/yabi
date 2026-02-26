#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "error_messages.h"

struct Stack {
        int stack[STACK_SIZE];
        int top;
};

typedef struct Stack Stack;

Stack *stack_init(void);

int stack_empty(Stack *self);

int stack_full(Stack *self);

int stack_push(Stack *self, int data);

int stack_pop(Stack *self);

#endif