#include "variables.h"
#include <stdio.h>
#include "arrays.h"
#include "actions.h"
#include "is_smh_compare.h"
#include "calculations.h"
#include <string.h>

void init_variable_arr(VARIABLE_ARR* var){
    var->current=var->max_size=0;
    var->arr=NULL;
}

void resize_var_arr(VARIABLE_ARR* var){
    VARIABLE* new_arr=(VARIABLE*)calloc(var->max_size*2+1,sizeof(VARIABLE));
    for (int i=0;i<var->current;++i){
        new_arr[i]=var->arr[i];
    }
    free(var->arr);
    var->arr=new_arr;
    var->max_size=var->max_size*2+1;
}

void push_variable(VARIABLE_ARR* arr,VARIABLE* var){
    if (arr->current==arr->max_size){
        resize_var_arr(arr);
    }
    arr->arr[arr->current++]=*var;
}

void print_variables(VARIABLE_ARR* arr){
    for (int i=0;i<arr->current;++i){
        printf("%s = %f\n",arr->arr[i].name,arr->arr[i].value.real_value);
    }
    printf("\n");
}

COMPLEX_NUM calculate_variables(VARIABLE_ARR* arr_var,VARIABLE* var){
    var->checked=1;
    ARRAY list,stack;
    init_arr(&list);
    init_arr(&stack);
    WORD buf;
    buf.current=0;
    memset(buf.st,0,sizeof(buf.st));
    int flag=0;

    for (int i=0;i<=strlen(var->str);++i){
        if (var->str[i]==' ') continue;

        if (!is_op_or_bracket(&var->str[i]) && i!=strlen(var->str)){
            buf.st[buf.current++]=var->str[i];
            flag=1;
//            printf("%s\n",buf.st);
        }
        else{
            if (flag==1 && !is_function(&buf)) {
                is_number_function_variable(&list,&buf); // __1__
            }
            if (flag==1 && is_function(&buf)) {
//                printf("%d\n",choose(buf.st));
                is_number_function_variable(&stack,&buf); // __2__
            }
            flag=0;

            if (var->str[i]=='(') is_open_bracket(&stack); // __3__
            if (var->str[i]==')') is_close_bracket(&stack,&list); //__4__
            if (is_op_or_bracket(&var->str[i]) && var->str[i]!='(' && var->str[i]!=')'){ // __5__
                if (is_u_min(&var->str[i],&var->str[i-1],i)){
                    is_un_minus(&stack);
                }
                else{
                    is_operator(&stack,&list,&var->str[i]);
                }
            }
        }
    }
    while (stack.current!=0){
        push(&list,&stack.str[stack.current-1]);
        --stack.current;
    }
//    arr_print(&list);
    COMPLEX_ARR new_stack;
    init_complex_arr(&new_stack);

    for (int i=0;i<list.current;++i){
        if (is_num(&list.str[i]) || is_const(&list.str[i])){
            is_num_or_const(&new_stack,&list.str[i]);
            continue;
        }
        if (is_function(&list.str[i]) || is_u_min(&list.str[i].st[0],&list.str[i].st[1],i)){
//            is_func_or_un_min(&new_stack,&list.str[i]);
            is_f(&new_stack,&list.str[i]);
            continue;
        }
        if (is_op_or_bracket(&list.str[i].st[0])){
            is_operation(&new_stack,&list.str[i]);
            continue;
        }
        for (int j=0;j<arr_var->current;++j){
            if (strcmp(arr_var->arr[j].name,list.str[i].st)==0){
                if (!arr_var->arr[j].checked){
                    arr_var->arr[j].value=calculate_variables(arr_var,&arr_var->arr[j]);
                }
                if (new_stack.current==new_stack.max_size){
                    resize_complex(&new_stack);
                }
                new_stack.arr[new_stack.current++]=arr_var->arr[j].value;
                break;
            }
//            printf("%s\n",variables.arr[j].name);
        }
    }

//    arr_print_double(&new_stack);
    return new_stack.arr[0];
}
