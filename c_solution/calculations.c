#include "calculations.h"
#include "is_smh_compare.h"
#include <string.h>
#include "operations_functions.h"

void is_num_or_const(COMPLEX_ARR * arr, WORD* word){
    if (is_num(word)){
        push_complex(arr, word);
    }
    else{
        WORD con;
        if (word->st[0]=='P' || word->st[0]=='p'){
            con.st[0]='3';
            con.st[1]='.';
            con.st[2]='1';
            con.st[3]='4';
            con.st[4]='1';
            con.st[5]='5';
            con.st[6]='9';
            con.st[7]='2';
            con.current=8;
        }

        if (word->st[0]=='e'){
            con.st[0]='2';
            con.st[1]='.';
            con.st[2]='7';
            con.st[3]='1';
            con.st[4]='8';
            con.st[5]='2';
            con.st[6]='8';
            con.st[7]='1';

            con.current=8;
        }
        if (word->st[0]=='j'){
            //TODO - know what 'j' is
        }
        push_complex(arr, &con);
    }
}

int choose (const char* str){
    char* functions[]={"cos","sin","tg", "ln","lg","sqrt","abs", "exp", "u-", "real","imag","mag","phase"};
    for (int i=0;i<13;++i){
        if (strcmp(str,functions[i])==0){
            return i;
        }
    }
    return -1;
}


void is_f(COMPLEX_ARR* arr, WORD* word){
    comp (*functions[])(comp)={ccos, csin, ctan, clog, clog10, csqrt, cabsd, cexp, u , creald, cimagd, mag, phase};
    arr->arr[arr->current-1]=functions[choose(word->st)](arr->arr[arr->current-1]);
}

int choose_c(char* str){
    char* operations[]={"+","-","*","/","^"};
    for (int i=0;i<5;++i){
        if (strcmp(str,operations[i])==0){
            return i;
        }
    }
    return -1;
}

void is_operation(COMPLEX_ARR * arr, WORD* word){
    comp (*operations[])(comp,comp)={plus,minus,multiplication,division,exponentiation};
    arr->arr[arr->current-2]=operations[choose_c(word->st)](arr->arr[arr->current-2],arr->arr[arr->current-1]);
    --arr->current;
}
