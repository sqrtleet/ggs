#include <string.h>
#include <stdlib.h>
#include "rpn.h"
#include "stack.h"

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int isDigit(char c) {
    return (c >= '0' && c <= '9');
}

int isVar(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int get_priority(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;
    } else if (c == '^') {
        return 3;
    }
    return 0;
}

int convert_to_rpn(char *arr, char *rpn_arr) {
    struct Stack stack;
    init_stack(&stack);

    int n = 0;

    for (size_t i = 0; i < strlen(arr); i++) {
        char c = arr[i];

        if (isDigit(c) || isVar(c)) {
            // Если символ - цифра или переменная, добавляем его в выходную строку.
            rpn_arr[n] = c;
            n++;
        } else if (c == '(') {
            // Если символ - открывающая скобка, помещаем её в стек.
            push(&stack, c);
        } else if (c == ')') {
            // Если символ - закрывающая скобка, извлекаем операторы из стека и добавляем их в выходную строку до открывающей скобки.
            while (!is_empty(&stack) && peek(&stack) != '(') {
                rpn_arr[n] = pop(&stack);
                n++;
                // 1 2 3 4 * *
            }
            // Убираем открывающую скобку из стека.
            if (!is_empty(&stack) && peek(&stack) == '(') {
                pop(&stack);
            }
        } else if (isOperator(c)) {
            // Если символ - оператор, извлекаем операторы из стека и добавляем их в выходную строку, пока приоритет текущего оператора больше или равен оператору на вершине стека.
            while (!is_empty(&stack) && get_priority(peek(&stack)) >= get_priority(c)) {
                rpn_arr[n] = pop(&stack);
                n++;
            }
            // Помещаем текущий оператор в стек.
            push(&stack, c);
        } else if (c == 's' || c == 'c') {
            // Обработка функций sin и cos
            push(&stack, c);
            i += 2;  // Пропустить символы 's' и открывающей скобки
        }
    }

    // Извлекаем оставшиеся операторы из стека и добавляем их в выходную строку.
    while (!is_empty(&stack)) {
        rpn_arr[n] = pop(&stack);
        n++;
    }

    // Завершаем выходную строку.
    rpn_arr[n] = '\0';

    free_mem(&stack);

    return 0;
}


char *get_rpn(char *arr, char **rpn_arr) {
    *rpn_arr = (char *) malloc((strlen(arr) + 1) * sizeof(char));
    convert_to_rpn(arr, *rpn_arr);
    return arr;
}

// (sin(2 * x) * cos(2 * x) + 2 * x / 4 * x) / 2
// sin2x*cos2x**2x*4/x*+2/