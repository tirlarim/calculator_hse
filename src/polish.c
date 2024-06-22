#include "arrays.h"
#include "actions.h"
#include "polish.h"
#include "is_smh_compare.h"
#include "calculations.h"
#include "calcFnAndVar/variables.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define expression_size 1000

char* readLine(char* str, int n, char** input) {
  if (**input == '\0')
    return NULL;

  char* start = str;
  while (--n > 0 && **input != '\0' && **input != '\n') {
    *str++ = *(*input)++;
  }
  if (**input == '\n') {
    *str++ = *(*input)++;
  }
  *str = '\0';
  return start;
}

char* Calculations(char* strIn) {
  ARRAY list, stack;
  init_arr(&list);
  init_arr(&stack);
  char expression[expression_size] = {0};
  char* output = calloc(expression_size, sizeof(*output));
  readLine(expression, expression_size, &strIn);
  size_t exprLen = strlen(expression);
  if (expression[exprLen - 1] == '\n')
    expression[exprLen - 1] = '\0';
  if (strlen(expression) == 0) {
    const char expressionError[] = "ERROR: Enter the expression\n";
    sprintf(output, "%s\n", expressionError);
    printf("%s", expressionError);
    return output;
  }
  WORD buf = {0};
  int flag = 0;
  int k_o = 0, k_z = 0;
  for (unsigned long i = 0; i <= strlen(expression); ++i) {
    if (expression[i] == ' ')
      continue;

    if (!is_op_or_bracket_or_comma(&expression[i]) && i != strlen(expression)) {
      buf.st[buf.current++] = expression[i];
      flag = 1;
    } else {
      if (flag == 1 && !is_function(&buf)) {
        is_number_function_variable(&list, &buf);
      }
      if (flag == 1 && is_function(&buf)) {
        is_number_function_variable(&stack, &buf);
      }
      flag = 0;
      if (expression[i] == '(') {
        ++k_o;
        is_open_bracket(&stack);
      }
      if (expression[i] == ')') {
        ++k_z;
        is_close_bracket(&stack, &list);
      }
      if (is_op_or_bracket_or_comma(&expression[i]) && expression[i] != '(' && expression[i] != ')') {
        if (is_u_min(&expression[i], &expression[i - 1], i)) {
          is_un_minus(&stack);
        } else {
          is_operator(&stack, &list, &expression[i]);
        }
      }
    }
  }
  if (k_o != k_z) {
    const char expressionError[] = "ERROR: Check brackets\n";
    sprintf(output, "%s", expressionError);
    printf("%s", expressionError);
    return output;
  }

  while (stack.current != 0) {
    push(&list, &stack.str[stack.current - 1]);
    --stack.current;
  }

  if (stack.current == 0 && list.current == 0) {
    const char expressionError[] = "ERROR: Enter the expression\n";
    sprintf(output, "%s", expressionError);
    printf("%s\n", expressionError);
    return output;
  }

  VARIABLE_ARR variables;
  init_variable_arr(&variables);
  int parceVarIndex = 0;

  // char* input = strIn;
  while (strIn[parceVarIndex] != '\0') {
    VARIABLE currenetVar;
    currenetVar.name[0] = 0;
    currenetVar.str[0] = 0;

    sscanf(&strIn[parceVarIndex], "%s = ", currenetVar.name);
    if (strlen(currenetVar.name) == 0) {
      break;
    }
    while (strIn[parceVarIndex] != '=') {
      parceVarIndex++;
    }
    if (strIn[parceVarIndex] == '=') {
      ++parceVarIndex;
    }
    while (strIn[parceVarIndex] == ' ') {
      ++parceVarIndex;
    }
    char* input = &strIn[parceVarIndex];
    readLine(currenetVar.str, 1000, &input);
    while (strIn[parceVarIndex] != '\n' && strIn[parceVarIndex] != '\0') {
      ++parceVarIndex;
    }
    currenetVar.str[strlen(currenetVar.str) - 1] = '\0';
    currenetVar.checked = 0;
    if (strlen(currenetVar.str) != 0) {
      push_variable(&variables, &currenetVar);
    }
  }
  for (int i = 0; i < variables.current; ++i) {
    if (!variables.arr[i].checked) {
      variables.arr[i].value = calculate_variables(output, &variables, &variables.arr[i]);
    }
  }

  COMPLEX_ARR new_stack;
  init_complex_arr(&new_stack);

  for (int i = 0; i < list.current; ++i) {
    if (is_num(&list.str[i]) || is_const(&list.str[i])) {
      is_num_or_const(&new_stack, &list.str[i]);
      continue;
    }
    if (is_function(&list.str[i]) || is_u_min(&list.str[i].st[0], &list.str[i].st[1], i)) {
      is_f(&new_stack, &list.str[i]);
      continue;
    }
    // if (is_2arg_function(&list.str[i])) {
    //   is_2arg_f(&new_stack, &list.str[i]);
    //   continue;
    // }
    if (is_op_or_bracket_or_comma(&list.str[i].st[0])) {
      is_operation(&new_stack, &list.str[i]);
      continue;
    }
    int fl = 0;
    for (int j = 0; j < variables.current; ++j) {
      if (strcmp(variables.arr[j].name, list.str[i].st) == 0) {
        fl = 1;
        if (new_stack.current == new_stack.max_size) {
          resize_complex(&new_stack);
        }
        new_stack.arr[new_stack.current++] = variables.arr[j].value;
        break;
      }
    }
    if (fl == 0) {
      sprintf(output, "ERROR: There is no variable %s \n", list.str[i].st);
      printf("ERROR: There is no variable %s \n", list.str[i].st);
      return output;
    }
  }

  int printIndex = 0;
  print_complex(output, &printIndex, new_stack.arr[0]);
#if 0  // For debug you can also print EXPRESSION and vars.
  printIndex += sprintf(&output[printIndex], "\n\nEXPRESSION: \n%s\n", expression);
  if (variables.current) {
    printIndex += sprintf(&output[printIndex], "\nVARIABLES:\n");
    print_variables(output, &printIndex, &variables);
  }
#endif
  return output;
}
