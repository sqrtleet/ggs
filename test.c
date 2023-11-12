#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 25
#define COLS 80
#define PI 3.14159265358979323846

// Определение констант
#define MIN_X (0.0)
#define MAX_X (4.0 * PI)
#define MIN_Y (-1.0)
#define MAX_Y (1.0)
#define CENTER_X MIN_X
#define CENTER_Y (ROWS - 1) / 2.0

// Прототипы функций
double calculateExpression(const char *expression, double x);
int isLetter(char c);
int isDigit(char c);
void infixToPostfix(const char *infixExpression, char *postfixExpression);
int precedence(char operator);
int isOperator(char c);

// Рекурсивная функция для вычисления выражения
double calculateExpression(const char *expression, double x) {
    if (!expression || *expression == '\0') {
        return 0.0;
    }

    char currentChar = *expression;

    if (isLetter(currentChar)) {
        return x;
    } else if (isDigit(currentChar) || (currentChar == '-' && isDigit(*(expression + 1)))) {
        return atof(expression);
    } else if (currentChar == 's' && *(expression + 1) == 'i' && *(expression + 2) == 'n') {
        return sin(calculateExpression(expression + 3, x));
    } else if (currentChar == 'c' && *(expression + 1) == 'o' && *(expression + 2) == 's') {
        return cos(calculateExpression(expression + 3, x));
    } else if (currentChar == '(') {
        // Пропускаем открывающую скобку
        int i = 1; // Счетчик открывающихся скобок
        int j = 1; // Счетчик закрывающихся скобок

        while (i != j && *(expression + i) != '\0') {
            if (*(expression + i) == '(') {
                i++;
            } else if (*(expression + i) == ')') {
                j++;
            } else {
                i++;
            }
        }

        if (*(expression + i) == '\0') {
            // Не хватает закрывающей скобки
            return 0.0;
        } else {
            // Пропускаем закрывающую скобку
            return calculateExpression(expression + i + 1, x);
        }
    } else {
        return 0.0;
    }
}

// Функция для проверки, является ли символ буквой
int isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Функция для проверки, является ли символ цифрой
int isDigit(char c) {
    return (c >= '0' && c <= '9');
}

// Функция, которая преобразует инфиксное выражение в постфиксное
void infixToPostfix(const char *infixExpression, char *postfixExpression) {
    char stack[100];
    int top = -1;
    size_t i, j;

    for (i = 0, j = 0; i < strlen(infixExpression); i++) {
        char c = infixExpression[i];

        if (c == ' ' || c == '\t') {
            continue;
        } else if (isDigit(c) || isLetter(c)) {
            postfixExpression[j++] = c;
        } else if (isOperator(c)) {
            while (top != -1 && precedence(stack[top]) >= precedence(c) && stack[top] != '(') {
                postfixExpression[j++] = stack[top--];
            }
            stack[++top] = c;
        } else if (c == '(') {
            stack[++top] = c;
        } else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                postfixExpression[j++] = stack[top--];
            }
            if (top != -1 && stack[top] == '(') {
                top--; // Удаляем открывающую скобку из стека
            }
        }
    }

    while (top != -1) {
        postfixExpression[j++] = stack[top--];
    }

    postfixExpression[j] = '\0';
}

// Функция для проверки, является ли символ оператором
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Функция, которая возвращает приоритет оператора
int precedence(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

int main() {
    char expression[100];
    fgets(expression, sizeof(expression), stdin);

    char postfixExpression[100];
    infixToPostfix(expression, postfixExpression);

    int p = 0;
    while (postfixExpression[p] != '\0') {
        printf("%c", postfixExpression[p]);
        p++;
    }

    char result[ROWS][COLS];

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            double x = MIN_X + (MAX_X - MIN_X) * j / (COLS - 1);
            double y = calculateExpression(postfixExpression, x);

            // Преобразование координат для учета центра координат
            int screenX = (int)round((x - MIN_X) / (MAX_X - MIN_X) * COLS);
            int screenY = (int)round((y - MIN_Y) / (MAX_Y - MIN_Y) * ROWS);

            if (screenX >= 0 && screenX < COLS && screenY >= 0 && screenY < ROWS) {
                result[screenY][screenX] = '*';
            }
        }
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c", result[i][j] == '*' ? '*' : '.');
        }
        printf("\n");
    }

    return 0;
}