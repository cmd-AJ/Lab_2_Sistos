#include <stdio.h>
#include <unistd.h>
int main(){
    int p = fork();
    if (p==0)
    {
        printf("%d \n", (int)getpid());
    }
    int p1 = fork();
    if (p1==0)
    {
        printf("%d \n", (int)getpid());
    }
    int p2 = fork();
    if (p==2)
    {
        printf("%d \n", (int)getpid());
    }
    int p3 = fork();
    if (p3==0)
    {
        printf("%d \n", (int)getpid());
    }
    return (0);
}
