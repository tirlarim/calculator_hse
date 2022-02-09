#include "actions.h"
#include <string.h>

void is_number_function_variable(ARRAY* arr,WORD* buf){
    push(arr,buf);
    buf->current=0;
    memset(buf->st,0,sizeof(buf->st));
}

void is_open_bracket(ARRAY* stack){
    WORD op_br;
    op_br.current=1;
    memset(op_br.st,0,sizeof(op_br));
    op_br.st[0]='(';
    push(stack,&op_br);
}

void is_close_bracket(ARRAY* stack, ARRAY* list){
    while (stack->str[stack->current-1].st[0]!='('){
        push(list,&stack->str[stack->current-1]);
        --stack->current;
    }
    --stack->current;
    if (is_function(&stack->str[stack->current-1])) {
        push(list,&stack->str[stack->current-1]);
        --stack->current;
    }
}

void is_operator(ARRAY* stack, ARRAY* list,const char* op){
    if (stack->current!=0) while (compare(op,&stack->str[stack->current-1].st[0])){
        push(list,&stack->str[stack->current-1]);
        --stack->current;
    }
    WORD ope;
    ope.current=1;
    memset(ope.st,0,sizeof(ope.st));
    ope.st[0]=*op;
    push(stack,&ope);
}

void is_un_minus(ARRAY* stack){
    WORD op_br;
    op_br.current=2;
    memset(op_br.st,0,sizeof(op_br));
    op_br.st[0]='u';
    op_br.st[1]='-';
    push(stack,&op_br);
}