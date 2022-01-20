#include "arrays.h"
#include "actions.h"
#include "polish.h"
#include "is_smh_compare.h"
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

    arr_print(&list);
//    printf("\n%d\n%d",list.current,(int)sizeof(list));

//too soon :)
//    ARRAY new_stack;
//    init_arr(&new_stack);
//    while (list.current!=0){
//        if (is_num(&list.str[list.current-1])){
//            push(&new_stack,&list.str[list.current-1]);
//            --list.current;
//        }
//        if (is_function(&list.str[list.current-1]) || (list.str[list.current-1].st[0]=='u' && list.str[list.current-1].st[1]=='-'))
//        {
//
//        }
//    }

    fclose(stdin);
    fclose(stdout);
}