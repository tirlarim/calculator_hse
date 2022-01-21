#include "arrays.h"
#include "actions.h"
#include "polish.h"
#include "is_smh_compare.h"
#include "calculations.h"
#include <stdio.h>
#include <string.h>

void Calculations(){
    freopen("../input.txt","r",stdin);
    freopen("../output.txt","w",stdout);

    ARRAY list,stack;
    init_arr(&list);
    init_arr(&stack);
    char expression[1000];
    gets(expression);
    WORD buf;
    buf.current=0;
    int flag=0;

    for (int i=0;i<=strlen(expression);++i){
        if (expression[i]==' ') continue;

        if (!is_op_or_bracket(&expression[i]) && i!=strlen(expression)){
            buf.st[buf.current++]=expression[i];
            flag=1;
        }
        else{
                if (flag==1 && !is_function(&buf)) is_number_function_variable(&list,&buf); // __1__
                if (flag==1 && is_function(&buf)) is_number_function_variable(&stack,&buf); // __2__
                flag=0;

                if (expression[i]=='(') is_open_bracket(&stack); // __3__
                if (expression[i]==')') is_close_bracket(&stack,&list); //__4__
                if (is_op_or_bracket(&expression[i]) && expression[i]!='(' && expression[i]!=')'){ // __5__
                    if (is_u_min(&expression[i],&expression[i-1],&i)){
                        is_un_minus(&stack);
                    }
                    else{
                        is_operator(&stack,&list,&expression[i]);
                    }
                }
        }
    }

    while (stack.current!=0){
        push(&list,&stack.str[stack.current-1]);
        --stack.current;
    }

    DOUBLE_ARR new_stack;
    init_double_arr(&new_stack);
    int o=0;

    for (int i=0;i<list.current;++i){
        if (is_num(&list.str[i]) || is_const(&list.str[i])){
            is_num_or_const(&new_stack,&list.str[i]);
            continue;
        }
        if (is_function(&list.str[i]) || is_u_min(&list.str[i].st[0],&list.str[i].st[1],&o)){
            is_func_or_un_min(&new_stack,&list.str[i]);
            continue;
        }
        if (is_op_or_bracket(&list.str[i].st[0])){
            is_operation(&new_stack,&list.str[i]);
            continue;
        }
    }

    arr_print_double(&new_stack);
    fclose(stdin);
    fclose(stdout);
}