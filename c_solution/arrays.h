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

void init_arr(ARRAY* arr);
void resize(ARRAY* arr);
void push(ARRAY* arr,WORD* word);
void arr_print(ARRAY* arr);

#endif