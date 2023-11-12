#ifndef RPN_H
#define RPN_H

#define MAX_STACK_SIZE 100

int isOperator(char);
int isDigit(char);
int isVar(char);
int get_priority(char);
int convert_to_rpn(char *arr, char *rpn_arr);
char *get_rpn(char *, char **);

#endif