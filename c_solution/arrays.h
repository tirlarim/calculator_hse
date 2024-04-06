#ifndef C_SOLUTION_ARRAYS_H
#define C_SOLUTION_ARRAYS_H
#include <complex.h>
#define comp double complex

typedef struct {
  char st[20];
  int current;
} WORD;

typedef struct {
  WORD* str;
  int max_size;
  int current;
} ARRAY;

typedef struct {
  comp* arr;
  int max_size;
  int current;
} COMPLEX_ARR;

void resize_complex(COMPLEX_ARR* arr);
void push_complex(COMPLEX_ARR* arr, WORD* word);
void init_complex_arr(COMPLEX_ARR* arr);
void init_arr(ARRAY* arr);
void push(ARRAY* arr, WORD* word);
void print_complex(comp n);

#endif