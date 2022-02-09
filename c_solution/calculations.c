#include "calculations.h"
#include "is_smh_compare.h"
#include <string.h>
#include <math.h>
#include "operations_functions.h"

void is_num_or_const(COMPLEX_ARR * arr, WORD* word){
    if (is_num(word)){
        push_complex(arr, word);
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
        push_complex(arr, &con);
    }
}

int choose (const char* str){
    char* functions[]={"cos","sin","tg", "ln","sqrt","abs", "exp", "u-", "real","imag","mag","phase"};
    for (int i=0;i<12;++i){
        if (strcmp(str,functions[i])==0){
            return i;
        }
    }
    return -1;
}


void is_f(COMPLEX_ARR* arr, WORD* word){
//    comp z=arr->arr[arr->current-1].real_value+arr->arr[arr->current-1].imag_value*I;
    comp (*functions[])(comp)={ccos,csin,ctan,clog,csqrt, cabsd,cexp, u ,creald,cimagd,mag,phase};
    int i=choose(word->st);
    if (i==-1) return;
    comp z=functions[i](arr->arr[arr->current-1].real_value+arr->arr[arr->current-1].imag_value*I);
    arr->arr[arr->current-1].real_value=creal(z);
    arr->arr[arr->current-1].imag_value=cimag(z);
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
    int i=choose_c(word->st);
    if (i==-1) return;
    comp z=operations[i](arr->arr[arr->current-2].real_value+arr->arr[arr->current-2].imag_value*I,arr->arr[arr->current-1].real_value+arr->arr[arr->current-1].imag_value*I);
    arr->arr[arr->current-2].real_value=creal(z);
    arr->arr[arr->current-2].imag_value=cimag(z);
    --arr->current;
//    if (word->st[0]=='+'){
//        arr->arr[arr->current-2].real_value+=arr->arr[arr->current-1].real_value;
//        --arr->current;
//    }
//    if (word->st[0]=='-'){
//        arr->arr[arr->current-2].real_value-=arr->arr[arr->current-1].real_value;
//        --arr->current;
//    }
//    if (word->st[0]=='*'){
//        arr->arr[arr->current-2].real_value*=arr->arr[arr->current-1].real_value;
//        --arr->current;
//    }
//    if (word->st[0]=='/'){
//        arr->arr[arr->current-2].real_value/=arr->arr[arr->current-1].real_value;
//        --arr->current;
//    }
//    if (word->st[0]=='^'){
//        arr->arr[arr->current-2].real_value=pow(arr->arr[arr->current-2].real_value,arr->arr[arr->current-1].real_value);
//        --arr->current;
//    }
}
