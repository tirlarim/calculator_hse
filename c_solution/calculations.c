#include "calculations.h"
#include "is_smh_compare.h"
#include <string.h>
#include <math.h>

void is_num_or_const(DOUBLE_ARR* arr, WORD* word){
    if (is_num(word)){
        push_double(arr, word);
    }
    else{
        WORD con;
        if (word->st[0]=='P'){
            con.st[0]='3';
            con.st[1]='.';
            con.st[2]='1';
            con.st[3]='4';
            con.current=4;
        }

        if (word->st[0]=='e'){
            con.st[0]='2';
            con.st[1]='.';
            con.st[2]='7';
            con.st[3]='1';
            con.st[4]='8';
            con.current=5;
        }
        if (word->st[0]=='j'){
            //TODO - know what 'j' is
        }
        push_double(arr, &con);
    }
}

void is_func_or_un_min(DOUBLE_ARR* arr, WORD* word){
    if (strcmp(word->st,"u-")==0){
        arr->arr[arr->current-1]=-arr->arr[arr->current-1];
    }
    if (strcmp(word->st,"sin")==0){
        arr->arr[arr->current-1]=sin(arr->arr[arr->current-1]);
    }
    if (strcmp(word->st,"cos")==0){
        arr->arr[arr->current-1]=cos(arr->arr[arr->current-1]);
    }
    if (strcmp(word->st,"tg")==0){
        arr->arr[arr->current-1]=tan(arr->arr[arr->current-1]);
    }
    if (strcmp(word->st,"ln")==0){
        arr->arr[arr->current-1]=log(arr->arr[arr->current-1]);
    }
    if (strcmp(word->st,"sqrt")==0){
        arr->arr[arr->current-1]=sqrt(arr->arr[arr->current-1]);
    }
    if (strcmp(word->st,"abs")==0){
        arr->arr[arr->current-1]=fabs(arr->arr[arr->current-1]);
    }
    if (strcmp(word->st,"exp")==0){
        arr->arr[arr->current-1]=exp(arr->arr[arr->current-1]);
    }
}

void is_operation(DOUBLE_ARR* arr, WORD* word){
    if (word->st[0]=='+'){
        arr->arr[arr->current-2]+=arr->arr[arr->current-1];
        --arr->current;
    }
    if (word->st[0]=='-'){
        arr->arr[arr->current-2]-=arr->arr[arr->current-1];
        --arr->current;
    }
    if (word->st[0]=='*'){
        arr->arr[arr->current-2]*=arr->arr[arr->current-1];
        --arr->current;
    }
    if (word->st[0]=='/'){
        arr->arr[arr->current-2]/=arr->arr[arr->current-1];
        --arr->current;
    }
    if (word->st[0]=='^'){
        arr->arr[arr->current-2]=pow(arr->arr[arr->current-2],arr->arr[arr->current-1]);
        --arr->current;
    }
}
