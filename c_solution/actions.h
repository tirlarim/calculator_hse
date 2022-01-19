#ifndef C_SOLUTION_FUNCTIONS_H
#define C_SOLUTION_FUNCTIONS_H
#include "arrays.h"
#include "is_smh_compare.h"

void is_number_function_variable(ARRAY* arr,WORD* buf);
void is_open_bracket(ARRAY* stack);
void is_close_bracket(ARRAY* stack, ARRAY* list);
void is_operator(ARRAY* stack, ARRAY* list,const char* op);
void is_un_minus(ARRAY* stack);

#endif
