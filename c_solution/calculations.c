#include "calculations.h"
#include "is_smh_compare.h"
#include <string.h>
#include <math.h>

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
    char* functions[]={"cos","sin","tg", "ln","sqrt","abs", "exp", "u-"
//                       , "real","imag","mag","phase"
    };
    for (int i=0;i<8;++i){
        if (strcmp(str,functions[i])==0){
            return i;
        }
    }
    return -1;
}

double u(double a) {return -a;}

void is_f(COMPLEX_ARR* arr, WORD* word){
    double (*functions[])(double)={cos,sin,tan,log,sqrt,fabs,exp, u
//                                   ,real,imag,mag,phase
    };
    int i=choose(word->st);
    if (i==-1) return;
    arr->arr[arr->current-1].real_value=functions[i](arr->arr[arr->current-1].real_value);
}

void is_operation(COMPLEX_ARR * arr, WORD* word){
    if (word->st[0]=='+'){
        arr->arr[arr->current-2].real_value+=arr->arr[arr->current-1].real_value;
        --arr->current;
    }
    if (word->st[0]=='-'){
        arr->arr[arr->current-2].real_value-=arr->arr[arr->current-1].real_value;
        --arr->current;
    }
    if (word->st[0]=='*'){
        arr->arr[arr->current-2].real_value*=arr->arr[arr->current-1].real_value;
        --arr->current;
    }
    if (word->st[0]=='/'){
        arr->arr[arr->current-2].real_value/=arr->arr[arr->current-1].real_value;
        --arr->current;
    }
    if (word->st[0]=='^'){
        arr->arr[arr->current-2].real_value=pow(arr->arr[arr->current-2].real_value,arr->arr[arr->current-1].real_value);
        --arr->current;
    }
}
