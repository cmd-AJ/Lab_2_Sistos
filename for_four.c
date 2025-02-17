#include <stdio.h>
#include <unistd.h>


int main(){
    int count = 4;
   for (int i = 0; i < count; i++)
   {
    int p = fork();
    if (p==0)
    {
        printf("%d \n", (int)getpid());
    }    
   }
   
    return (0);
}
