#include "arrays.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    printf("\n");
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
//    printf("%s\n",word->st);
//    printf("%f",strtod(word->st,(char**)&word->st[0]));
//    arr->arr[arr->current].real_value=arr->arr[arr->current++].imag_value=0;
    if (strcmp(word->st,"j")==0){
        arr->arr[arr->current++]=I;
    }
    else arr->arr[arr->current++]=strtod(word->st,(char**)&word->st[0]);
}

void print_complex(comp n){
//    if ((int)n==n) printf("%.0f ",n);
//    else {
//        if (n==2.718){
//            printf("%.3f",n);
//        }
//        if (n==3.14)printf("%.2f ",n);
//        else printf("%.5f ",n);
//    }
    printf("%f %f\n",creal(n),cimag(n));
}

void arr_print_complex(COMPLEX_ARR * arr){
    for (int i=0;i<arr->current;++i){
//        if ((int)arr->arr[i]==arr->arr[i]) printf("%.0f ",arr->arr[i]);
//        else {
//            if (arr->arr[i]==2.718){
//                printf("%.3f",arr->arr[i]);
//                continue;
//            }
//            if (arr->arr[i]==3.14)printf("%.2f ",arr->arr[i]);
//            else printf("%.5f ",arr->arr[i]);
//        }
        print_complex(arr->arr[i]);
    }
//    printf("\n");
}