#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(){
    
    int p = fork();
    if (p==0)
    {

        for (int i = 0; i < 4000000; i++)
        {
            printf("%d \n", i);
        }
    } else
    {
        while (1){  }
        
    }

    return (0);
}
