#include "arrays.h"
#include <stdio.h>
#include <stdlib.h>

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

void arr_print(ARRAY* arr){
    for(int i=0;i<arr->current;++i){
        printf("%s ",arr->str[i].st);
    }
}




void init_double_arr(DOUBLE_ARR* arr){
    arr->current=arr->max_size=0;
    arr->arr=NULL;
}

void resize_double(DOUBLE_ARR* arr){
    double* new=(double*)calloc(arr->max_size*2+1,sizeof(double));
    for (int i=0;i<arr->current;++i){
        new[i]=arr->arr[i];
    }
    free(arr->arr);
    arr->arr=new;
    arr->max_size=arr->max_size*2+1;
}

void push_double(DOUBLE_ARR * arr, WORD* word){
    if (arr->current==arr->max_size){
        resize_double(arr);
    }
    arr->arr[arr->current++]=strtod(word->st,(char**)&word->st[0]);
}

void arr_print_double(DOUBLE_ARR * arr){
    for (int i=0;i<arr->current;++i){
        if ((int)arr->arr[i]==arr->arr[i]) printf("%.0f ",arr->arr[i]);
        else {
            if (arr->arr[i]==3.14)printf("%.2f ",arr->arr[i]);
            else printf("%f ",arr->arr[i]);
        }
    }
}