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

int choose (const char* str){
    char* functions[]={"cos","sin","tg", "ln","sqrt","abs", "exp", "u-"
//                       , "real","imag","mag","phase"
    };
    for (int i=0;i<13;++i){
        if (strcmp(str,functions[i])==0){
            return i;
        }
    }
    return -1;
}

double u(double a) {return -a;}

void is_f(DOUBLE_ARR* arr, WORD* word){
    double (*functions[])(double)={cos,sin,tan,log,sqrt,fabs,exp, u
//                                   ,real,imag,mag,phase
    };
    arr->arr[arr->current-1]=functions[choose(word->st)](arr->arr[arr->current-1]);
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
