#ifndef C_SOLUTION_ARRAYS_H
#define C_SOLUTION_ARRAYS_H

typedef struct{
    char st[20];
    int current;
}WORD;

typedef struct{
    WORD* str;
    int max_size;
    int current;
}ARRAY;

typedef struct{
    double* arr;
    int max_size;
    int current;
}DOUBLE_ARR;

typedef struct{
    char real[30];
    char imag[30];
    float real_value;
    float imag_value;
}COMPLEX_NUM;

void resize_double(DOUBLE_ARR* arr);
void push_double(DOUBLE_ARR * arr, WORD* word);
void arr_print_double(DOUBLE_ARR * arr);
void init_double_arr(DOUBLE_ARR* arr);
void init_arr(ARRAY* arr);
void resize(ARRAY* arr);
void push(ARRAY* arr,WORD* word);
void arr_print(ARRAY* arr);
void print_double(double n);

#endif