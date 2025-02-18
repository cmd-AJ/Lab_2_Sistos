#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(){
    
    int p = fork();
    if (p==0)
    {
        printf("%d \n", (int)getpid());
        exit(0);
    } else
    {
        while (1){  }
        
    }

    return (0);
}
