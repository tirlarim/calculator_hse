#ifndef C_SOLUTION_IS_SMH_COMPARE_H
#define C_SOLUTION_IS_SMH_COMPARE_H
#include "arrays.h"

int is_dig(const char* s);
int is_u_min(const char* s, const char* previous_s,int i);
int is_op_or_bracket_or_comma(const char* s);
int is_num(const WORD* word);
int is_function(const WORD* word);
int is_const(const WORD* word);
int compare(const char* to, const char* vs);

#endif