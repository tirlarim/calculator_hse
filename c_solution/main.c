#include <stdio.h>
#include "arrays.h"

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    ARRAY list,stack;
    init_arr(&list);
    init_arr(&stack);
    WORD str;

    while(!feof(stdin)){
        scanf("%s",str.st);
        add(&list,&str);
    }

    arr_print(&list);

    fclose(stdin);
    fclose(stdout);
    return 0;
}
