#include <stdio.h>

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int n;
    scanf("%d",&n);
    printf("%d",n);

    fclose(stdin);
    fclose(stdout);
    return 0;
}
