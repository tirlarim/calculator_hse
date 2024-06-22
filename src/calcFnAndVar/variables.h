#ifndef C_SOLUTION_VARIABLES_H
#define C_SOLUTION_VARIABLES_H
#include "../arrays.h"

typedef struct{
    char name[20];
    char str[1000];
    comp value;
    int checked;
}VARIABLE;

typedef struct{
    VARIABLE* arr;
    int current;
    int max_size;
}VARIABLE_ARR;

void init_variable_arr(VARIABLE_ARR* var);
void push_variable(VARIABLE_ARR* arr,VARIABLE* var);
void print_variables(char* outPtr, int* index, VARIABLE_ARR* arr);
comp calculate_variables(char* output, VARIABLE_ARR* arr_var,VARIABLE* var);

#endif
