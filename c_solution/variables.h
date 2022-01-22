#ifndef C_SOLUTION_VARIABLES_H
#define C_SOLUTION_VARIABLES_H
#include <stdlib.h>

typedef struct{
    char name[20];
    char str[1000];
    double value;
    int checked;
}VARIABLE;

typedef struct{
    VARIABLE* arr;
    int current;
    int max_size;
}VARIABLE_ARR;

void init_variable_arr(VARIABLE_ARR* var);
void resize_var_arr(VARIABLE_ARR* var);
void push_variable(VARIABLE_ARR* arr,VARIABLE* var);
void print_variables(VARIABLE_ARR* arr);
double calculate_variables(VARIABLE_ARR* arr_var,VARIABLE* var);

#endif
