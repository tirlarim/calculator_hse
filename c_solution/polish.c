#include "arrays.h"
#include "actions.h"
#include "polish.h"
#include "is_smh_compare.h"
#include "calculations.h"
#include <stdio.h>
#include <string.h>
#include "variables.h"
#define expression_size 1000

COMPLEX_NUM Calculations(){
    freopen("../input.txt","r",stdin);
    freopen("../output.txt","w",stdout);

    ARRAY list,stack;
    init_arr(&list);
    init_arr(&stack);
    char expression[expression_size];
    gets(expression);
    if (strlen(expression)==0){
        printf("Enter the expression\n");
        exit(0);
    }
    WORD buf;
    memset(buf.st,0,sizeof(buf.st));
    buf.current=0;
    int flag=0;
    for (int i=0;i<=strlen(expression);++i){
        if (expression[i]==' ') continue;

        if (!is_op_or_bracket(&expression[i]) && i!=strlen(expression)){
            buf.st[buf.current++]=expression[i];
            flag=1;
        }
        else{
                if (flag==1 && !is_function(&buf)) {
                    is_number_function_variable(&list,&buf); // __1__
                }
                if (flag==1 && is_function(&buf)) {
//                    printf("%d\n",choose(buf.st));
                    is_number_function_variable(&stack,&buf); // __2__
                }
                flag=0;

                if (expression[i]=='(') is_open_bracket(&stack); // __3__
                if (expression[i]==')') is_close_bracket(&stack,&list); //__4__
                if (is_op_or_bracket(&expression[i]) && expression[i]!='(' && expression[i]!=')'){ // __5__
                    if (is_u_min(&expression[i],&expression[i-1],i)){
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
    //-------------------- variables

    printf("--\n");
    arr_print(&list);
    printf("--\n");

    VARIABLE_ARR variables;
    init_variable_arr(&variables);
    while (!feof(stdin)){
        VARIABLE new;
        new.str[0]=0;
        scanf("%s = ",new.name);
        if (strlen(new.name)==0) break;
        gets(new.str);
        new.checked=0;
        if (strlen(new.str)!=0)
            push_variable(&variables,&new);
        new.str[0]=0;
    }

    for (int i=0;i<variables.current;++i){
        if (!variables.arr[i].checked){
            variables.arr[i].value=calculate_variables(&variables,&variables.arr[i]);
        }
    }

    //--------------------

    COMPLEX_ARR new_stack;
    init_complex_arr(&new_stack);

    for (int i=0;i<list.current;++i){
        if (is_num(&list.str[i]) || is_const(&list.str[i])){
            is_num_or_const(&new_stack,&list.str[i]);
            continue;
        }
        if (is_function(&list.str[i]) || is_u_min(&list.str[i].st[0],&list.str[i].st[1],i)){
            is_f(&new_stack,&list.str[i]);
//            is_func_or_un_min(&new_stack,&list.str[i]);
            continue;
        }
        if (is_op_or_bracket(&list.str[i].st[0])){
            is_operation(&new_stack,&list.str[i]);
            continue;
        }
        for (int j=0;j<variables.current;++j){
            if (strcmp(variables.arr[j].name,list.str[i].st)==0){
                if (new_stack.current==new_stack.max_size){
                    resize_complex(&new_stack);
                }
                new_stack.arr[new_stack.current++]=variables.arr[j].value;
                break;
            }
        }
//        arr_print_double(&new_stack);
    }
    print_variables(&variables);
    printf("%s = ",expression);
    return new_stack.arr[0];
}
