#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// Инициализация стека
void init_stack(struct Stack *stack) {
    stack->arr = (char *)malloc(sizeof(char));
    stack->top = -1;
    stack->size = 1;
}

// Проверка на пустоту стека
int is_empty(struct Stack *stack) {
    return (stack->top == -1);
}

// Увеличение ёмкости стека при необходимости
void increase_size(struct Stack *stack) {
    int new_size = stack->size + 1;
    stack->arr = (char *)realloc(stack->arr, new_size * sizeof(char));
    stack->size = new_size;
}

// Добавление элемента в стек
void push(struct Stack *stack, char c) {
    if (stack->top == stack->size - 1) {
        increase_size(stack);
    }
    stack->arr[++stack->top] = c;
}

// Удаление элемента из стека и возврат его значения
char pop(struct Stack *stack) {
    if (!is_empty(stack)) {
        return stack->arr[stack->top--];
    } else {
        printf("Стек пуст.\n");
        return -1; // Возвращаем значение по умолчанию
    }
}

// Получение верхнего элемента стека без его удаления
char peek(struct Stack *stack) {
    if (!is_empty(stack)) {
        return stack->arr[stack->top];
    } else {
        printf("Стек пуст.\n");
        return -1; // Возвращаем значение по умолчанию
    }
}

// Освобождение памяти, выделенной для стека
void free_mem(struct Stack *stack) {
    free(stack->arr);
}