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
    double real_value;
    double imag_value;
}COMPLEX_NUM;

typedef struct{
    COMPLEX_NUM* arr;
    int max_size;
    int current;
}COMPLEX_ARR;

void resize_complex(COMPLEX_ARR* arr);
void push_complex(COMPLEX_ARR * arr, WORD* word);
void arr_print_complex(COMPLEX_ARR * arr);
void init_complex_arr(COMPLEX_ARR* arr);
void init_arr(ARRAY* arr);
void resize(ARRAY* arr);
void push(ARRAY* arr,WORD* word);
void arr_print(ARRAY* arr);
void print_complex(COMPLEX_NUM n);

#endif