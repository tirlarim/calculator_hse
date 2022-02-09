#include "arrays.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void init_arr(ARRAY* arr){
    arr->current=arr->max_size=0;
    arr->str=NULL;
}

void resize(ARRAY* arr){
    WORD* new_arr=(WORD*)calloc(arr->max_size*2+1,sizeof(WORD));
    for (int i=0;i<arr->current;++i){
        new_arr[i]=arr->str[i];
    }
    free(arr->str);
    arr->str=new_arr;
    arr->max_size=arr->max_size*2+1;
}

void push(ARRAY* arr, WORD* word){
    if (arr->current==arr->max_size){
        resize(arr);
    }
    arr->str[arr->current++]=*word;
}


void init_complex_arr(COMPLEX_ARR * arr){
    arr->current=arr->max_size=0;
    arr->arr=NULL;
}

void resize_complex(COMPLEX_ARR* arr){
    comp* new=(comp *)calloc(arr->max_size*2+1,sizeof(comp));
    for (int i=0;i<arr->current;++i){
        new[i]=arr->arr[i];
    }
    free(arr->arr);
    arr->arr=new;
    arr->max_size=arr->max_size*2+1;
}

void push_complex(COMPLEX_ARR* arr, WORD* word){
    if (arr->current==arr->max_size){
        resize_complex(arr);
    }
    if (strcmp(word->st,"pi")==0){
        arr->arr[arr->current++]=M_PI;
        return;
    }
    if (strcmp(word->st,"PI")==0){
        arr->arr[arr->current++]=M_PI;
        return;
    }
    if (strcmp(word->st,"e")==0){
        arr->arr[arr->current++]=M_E;
        return;
    }
    if (strcmp(word->st,"j")==0){
        arr->arr[arr->current++]=I;
        return;
    }
    arr->arr[arr->current++]=strtod(word->st,(char**)&word->st[0]);
}

void print_complex(comp n){
    double x=creal(n), y=cimag(n);
    if (x!=0){
        printf("%g",x);
        if (y!=0){
            if (y>0) printf("+");
            printf("%g*j",y);
        }
    }
    else{
        printf("%g*j",y);
    }
}
