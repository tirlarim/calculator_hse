#include "arrays.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void init_arr(ARRAY* arr) {
  arr->current = arr->max_size = 0;
  arr->str = NULL;
}

void resize(ARRAY* arr) {
  arr->max_size = arr->max_size * 2 + 1;
  WORD* new_arr = calloc(arr->max_size, sizeof(WORD));
  memcpy(new_arr, arr->str, arr->current * sizeof(*arr->str));
  free(arr->str);
  arr->str = new_arr;
}

void push(ARRAY* arr, const WORD* word) {
  if (arr->current == arr->max_size) {
    resize(arr);
  }
  arr->str[arr->current].current = word->current;
  memcpy(arr->str[arr->current].st, word->st, 20);
  ++arr->current;
}

void init_complex_arr(COMPLEX_ARR* arr) {
  arr->current = arr->max_size = 0;
  arr->arr = NULL;
}

void resize_complex(COMPLEX_ARR* arr) {
  comp* new = (comp*)calloc(arr->max_size * 2 + 1, sizeof(comp));
  for (int i = 0; i < arr->current; ++i) {
    new[i] = arr->arr[i];
  }
  free(arr->arr);
  arr->arr = new;
  arr->max_size = arr->max_size * 2 + 1;
}

void push_complex(COMPLEX_ARR* arr, WORD* word) {
  if (arr->current == arr->max_size) {
    resize_complex(arr);
  }
  if (strcmp(word->st, "π") == 0 || strcmp(word->st, "pi") == 0 || strcmp(word->st, "PI") == 0) {
    arr->arr[arr->current++] = M_PI;
    return;
  }
  if (strcmp(word->st, "e") == 0) {
    arr->arr[arr->current++] = M_E;
    return;
  }
  if (strcmp(word->st, "j") == 0) {
    arr->arr[arr->current++] = I;
    return;
  }
  arr->arr[arr->current++] = strtod(word->st, (char**)&word->st[0]);
}

void print_complex(char* outPtr, int* index, comp n) {
  const double x = creal(n);
  const double y = cimag(n);
  if (x == 0 && y == 0) {
    *index += sprintf(&outPtr[*index], "0");
    return;
  }
  if (x != 0) {
    *index += sprintf(&outPtr[*index], "%g", x);
    if (y != 0) {
      if (y == 1) {
        *index += sprintf(&outPtr[*index], "+j");
        return;
      }
      if (y == -1) {
        *index += sprintf(&outPtr[*index], "-j");
        return;
      }
      if (y > 0)
        *index += sprintf(&outPtr[*index], "+");
      *index += sprintf(&outPtr[*index], "%g*j", y);
    }
  } else {
    if (y == 1) {
      *index += sprintf(&outPtr[*index], "j");
      return;
    }
    if (y == -1) {
      *index += sprintf(&outPtr[*index], "-j");
      return;
    }
    *index += sprintf(&outPtr[*index], "%g*j", y);
  }
}
