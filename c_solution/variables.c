#include "variables.h"
#include "arrays.h"
#include "actions.h"
#include "is_smh_compare.h"
#include "calculations.h"
#include <stdio.h>
#include <stdlib.h>
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
        printf("%s = ",arr->arr[i].name);
        print_complex(arr->arr[i].value);
        printf("\n");
    }
}

comp calculate_variables(VARIABLE_ARR* arr_var,VARIABLE* var){
    var->checked=1;
    ARRAY list,stack;
    init_arr(&list);
    init_arr(&stack);
    WORD buf;
    buf.current=0;
    memset(buf.st,0,sizeof(buf.st));
    int flag=0;
    int k_o=0,k_z=0;
    for (int i=0;i<=strlen(var->str);++i){
        if (var->str[i]==' ') continue;

        if (!is_op_or_bracket(&var->str[i]) && i!=strlen(var->str)){
            buf.st[buf.current++]=var->str[i];
            flag=1;
        }
        else{
            if (flag==1 && !is_function(&buf)) {
                is_number_function_variable(&list,&buf);
            }
            if (flag==1 && is_function(&buf)) {
                is_number_function_variable(&stack,&buf);
            }
            flag=0;

            if (var->str[i]=='(') {
                ++k_o;
                is_open_bracket(&stack);
            }
            if (var->str[i]==')') {
                ++k_z;
                is_close_bracket(&stack,&list);
            }
            if (is_op_or_bracket(&var->str[i]) && var->str[i]!='(' && var->str[i]!=')'){
                if (is_u_min(&var->str[i],&var->str[i-1],i)){
                    is_un_minus(&stack);
                }
                else{
                    is_operator(&stack,&list,&var->str[i]);
                }
            }
        }
    }

    if (k_o!=k_z) {
        printf("ERROR:\nCheck brackets in the variable %s\n",var->name);
        exit(1);
    }

    while (stack.current!=0){
        push(&list,&stack.str[stack.current-1]);
        --stack.current;
    }
    COMPLEX_ARR new_stack;
    init_complex_arr(&new_stack);

    for (int i=0;i<list.current;++i){
        if (is_num(&list.str[i]) || is_const(&list.str[i])){
            is_num_or_const(&new_stack,&list.str[i]);
            continue;
        }
        if (is_function(&list.str[i]) || is_u_min(&list.str[i].st[0],&list.str[i].st[1],i)){
            is_f(&new_stack,&list.str[i]);
            continue;
        }
        if (is_op_or_bracket(&list.str[i].st[0])){
            is_operation(&new_stack,&list.str[i]);
            continue;
        }
        int fl=0;
        for (int j=0;j<arr_var->current;++j){
            if (strcmp(arr_var->arr[j].name,list.str[i].st)==0){
                fl=1;
                if (!arr_var->arr[j].checked){
                    arr_var->arr[j].value=calculate_variables(arr_var,&arr_var->arr[j]);
                }
                if (new_stack.current==new_stack.max_size){
                    resize_complex(&new_stack);
                }
                new_stack.arr[new_stack.current++]=arr_var->arr[j].value;
                break;
            }
        }
        if (fl==0) {
            printf("ERROR:\nThere is no variable %s\n",list.str[i].st);
            exit(1);
        }

    }
    return new_stack.arr[0];
}
