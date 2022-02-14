#include "arrays.h"
#include "actions.h"
#include "polish.h"
#include "is_smh_compare.h"
#include "calculations.h"
#include "variables.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define expression_size 1000

void Calculations(){

    char *HomePath = getenv("USERPROFILE");
    char pathInput[200] = {0}; char pathOutput[200] = {0};
    char filePathInput[] = "\\AppData\\Local\\HSE-Calculator\\storage\\input.txt";
    char filePathOutput[] = "\\AppData\\Local\\HSE-Calculator\\storage\\output.txt";
    strncat(pathInput, HomePath, 120);
    strncat(pathInput, filePathInput, 120);
    strncat(pathOutput, HomePath, 120);
    strncat(pathOutput, filePathOutput, 120);

    freopen(pathInput,"r",stdin);
    freopen(pathOutput,"w",stdout);

    ARRAY list,stack;
    init_arr(&list);
    init_arr(&stack);
    char expression[expression_size];
    gets(expression);
    if (strlen(expression)==0){
//        printf("ERROR:\nEnter the expression\n");
//        exit(0);
        printf("ERROR: Enter the expression\n");
        fclose(stdin);
        fclose(stdout);
        return;
    }
    WORD buf;
    memset(buf.st,0,sizeof(buf.st));
    buf.current=0;
    int flag=0;
    int k_o=0,k_z=0;
    for (int i=0;i<=strlen(expression);++i){
        if (expression[i]==' ') continue;

        if (!is_op_or_bracket_or_comma(&expression[i]) && i != strlen(expression)){
            buf.st[buf.current++]=expression[i];
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
                if (expression[i]=='(') {
                    ++k_o;
                    is_open_bracket(&stack);
                }
                if (expression[i]==')') {
                    ++k_z;
                    is_close_bracket(&stack,&list);
                }
                if (is_op_or_bracket_or_comma(&expression[i]) && expression[i] != '(' && expression[i] != ')'){
                    if (is_u_min(&expression[i],&expression[i-1],i)){
                        is_un_minus(&stack);
                    }
                    else{
                            is_operator(&stack,&list,&expression[i]);
                    }
                }
        }
    }
    if (k_o!=k_z) {
//        printf("ERROR:\nCheck brackets in the expression\n");
//        exit(0);
        printf("ERROR: Check brackets\n");
        fclose(stdin);
        fclose(stdout);
        return;
    }

    while (stack.current!=0){
        push(&list,&stack.str[stack.current-1]);
        --stack.current;
    }

    if (stack.current==0 && list.current==0){
//        printf("ERROR:\nEnter the expression\n");
//        exit(0);
        printf("ERROR: Enter the expression\n");
        fclose(stdin);
        fclose(stdout);
        return;
    }

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
        if (is_op_or_bracket_or_comma(&list.str[i].st[0])){
            is_operation(&new_stack,&list.str[i]);
            continue;
        }
        int fl=0;
        for (int j=0;j<variables.current;++j){
            if (strcmp(variables.arr[j].name,list.str[i].st)==0){
                fl=1;
                if (new_stack.current==new_stack.max_size){
                    resize_complex(&new_stack);
                }
                new_stack.arr[new_stack.current++]=variables.arr[j].value;
                break;
            }
        }
        if (fl==0){
//            printf("ERROR:\nThere is no variable %s\n",list.str[i].st);
//            exit(0);
            printf("ERROR: There is no variable %s ",list.str[i].st);
            fclose(stdin);
            fclose(stdout);
            return;
        }
    }

    //printf("RESULT:\n");
    print_complex(new_stack.arr[0]);
    printf("\n\nEXPRESSION: \n%s\n",expression);
    if (variables.current){
        printf("\nVARIABLES:\n");
        print_variables(&variables);
    }

    fclose(stdin);
    fclose(stdout);
}
