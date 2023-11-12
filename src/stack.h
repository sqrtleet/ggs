#ifndef STACK_H
#define STACK_H

struct Stack {
    char *arr;
    int top;
    int size;
};

void init_stack(struct Stack *);
int is_empty(struct Stack *);
void increase_size(struct Stack *);
void push(struct Stack *, char);
char pop(struct Stack *);
char peek(struct Stack *);
void free_mem(struct Stack *);

#endif