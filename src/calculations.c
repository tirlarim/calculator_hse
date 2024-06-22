#include "calculations.h"
#include "is_smh_compare.h"
#include "calcFnAndVar/operations_functions.h"
#include <string.h>

void is_num_or_const(COMPLEX_ARR* arr, WORD* word) {
  push_complex(arr, word);
}

static int choose(const char* str) {
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
  const int index = choose(word->st);
  comp z = arr->arr[arr->current - 1];
  double real = creal(z);
  double image = cimag(z);
  if (image == 0.0 || image == -0.0)
    z = real + 0.0 * I; // -0.0i give incorrect result -> 0-j
  arr->arr[arr->current - 1] = functions[index](z);
}

// static int choose2ArgFun(const char* str) {
//   char* functions[] = {"pow", "log"};
//   for (int i = 0; i < 2; ++i) {
//     if (strcmp(str, functions[i]) == 0) {
//       return i;
//     }
//   }
//   return -1;
// }
//
// void is_2arg_f(COMPLEX_ARR* arr, WORD* word) {
//   if (arr->current - 2 < 0)
//     return;
//   comp (*functions[])(comp, comp) = {exponentiation, full_log};
//   const int index = choose2ArgFun(word->st);
//   comp z1 = arr->arr[arr->current - 2], z2 = arr->arr[arr->current - 1];
//   if (cimag(z1) == -0.0)
//     z1 = creal(z1) + 0.0 * I;
//   if (cimag(z2) == -0.0)
//     z2 = creal(z2) + 0.0 * I;
//   arr->arr[arr->current - 2] = functions[index](z1, z2);
//   --arr->current;
// }

static int choose_c(const char* str) {
  char* operations[] = {"+", "-", "*", "/", "^", ","};
  for (int i = 0; i < 6; ++i) {
    if (strcmp(str, operations[i]) == 0) {
      return i;
    }
  }
  return -1;
}

void is_operation(COMPLEX_ARR* arr, const WORD* word) {
  comp (*operations[])(comp, comp) = {plus, minus, multiplication, division, exponentiation, full_log};
  const int index = choose_c(word->st);
  arr->arr[arr->current - 2] = operations[index](arr->arr[arr->current - 2], arr->arr[arr->current - 1]);
  --arr->current;
}
