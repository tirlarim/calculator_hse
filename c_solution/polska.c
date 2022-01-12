#include "arrays.h"
#include "polska.h"
#include "is_smh.h"
#include <stdio.h>
#include <string.h>

void Parse(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    ARRAY list,stack;
    init_arr(&list);
    init_arr(&stack);
    char expression[1000];
    gets(expression);
    WORD buf;
    buf.current=0;

    for (int i=0;i<=strlen(expression);++i){
        if (expression[i]==' ') continue;
        if (is_op_or_bracket(&expression[i]) || i==strlen(expression)){
            if (is_num(&buf) || !is_function(&buf) || is_const(&buf)){
                if (strlen(buf.st)!=0) push(&list,&buf);
            }
            else{
                if (strlen(buf.st)!=0) push(&stack,&buf);
            }
            buf.current=0;
            memset(buf.st,0,sizeof(buf.st));

            WORD op;
            if (expression[i]=='('){
                op.st[0]='(';
                push(&stack,&op);
                op.current=0;
                memset(op.st,0,sizeof(op.st));
                continue;
            }
            if (expression[i]==')'){
                while(stack.str[stack.current].st[0]!='('){
                    if(stack.str[stack.current].current!=0)push(&list,&stack.str[stack.current]);
                    --stack.current;
                }
                --stack.current;
                printf("%s",list.str[list.current].st);
                if (is_function(&stack.str[stack.current])){
                    push(&list,&stack.str[stack.current]);
                    --stack.current;
                }
            }

        }
        else{
            buf.st[buf.current++]=expression[i];
        }
    }
    arr_print(&list);
    printf("\n");
    arr_print(&stack);

    fclose(stdin);
    fclose(stdout);
}