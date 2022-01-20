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

void resize_double(DOUBLE_ARR* arr);
void push_double(DOUBLE_ARR * arr, WORD* word);
void arr_print_double(DOUBLE_ARR * arr);
void init_double_arr(DOUBLE_ARR* arr);
void init_arr(ARRAY* arr);
void resize(ARRAY* arr);
void push(ARRAY* arr,WORD* word);
void arr_print(ARRAY* arr);

#endif