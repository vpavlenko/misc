#ifndef _MY_STACK
#define _MY_STACK

typedef int stack_t;

#define STACK_SIZE = 15;

typedef struct {
    int size;
    stack_t *values;
} Stack;

int stack_ok(Stack *stack);

// other methods

#endif // _MY_STACK 