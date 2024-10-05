#include <stdio.h>
#include <unistd.h>

int main() {
int s;
printf("enter a number");
scanf("%d",&s);

if (s>0){
    printf(" cowndown begins  ");
    while (s >= 0){
    printf("%d\n",s);
    sleep(1);
    s--;
    }
    printf("cowndown ends "); 
}
else{
printf("enter a valid number") ;
}
    return 0;
}

