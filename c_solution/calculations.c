#include "calculations.h"
#include "is_smh_compare.h"
#include "operations_functions.h"
#include <string.h>

void is_num_or_const(COMPLEX_ARR* arr, WORD* word) {
  push_complex(arr, word);
}

int choose(const char* str) {
  char* functions[] = {"cos", "sin", "tg", "ln", "lg", "sqrt", "abs", "exp", "u-", "real", "imag", "mag", "phase", "log"};
  for (int i = 0; i < 14; ++i) {
    if (strcmp(str, functions[i]) == 0) {
      return i;
    }
  }
  return -1;
}

void is_f(COMPLEX_ARR* arr, WORD* word) {
  comp (*functions[])(comp) = {ccos, csin, ctan, clog, clog10, csqrt, cabsd, cexp, u, creald, cimagd, mag, phase, empty};
  arr->arr[arr->current - 1] = functions[choose(word->st)](arr->arr[arr->current - 1]);
}

int choose_c(char* str) {
  char* operations[] = {"+", "-", "*", "/", "^", ","};
  for (int i = 0; i < 6; ++i) {
    if (strcmp(str, operations[i]) == 0) {
      return i;
    }
  }
  return -1;
}

void is_operation(COMPLEX_ARR* arr, WORD* word) {
  comp (*operations[])(comp, comp) = {plus, minus, multiplication, division, exponentiation, full_log};
  arr->arr[arr->current - 2] = operations[choose_c(word->st)](arr->arr[arr->current - 2], arr->arr[arr->current - 1]);
  --arr->current;
}
