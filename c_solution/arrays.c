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