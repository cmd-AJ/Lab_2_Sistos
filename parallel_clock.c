#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){

    pid_t pid1;
    pid_t pid2;
    pid_t pid3;

    clock_t time1;
    clock_t time2;

    time1 = clock();

    int p1 = fork();

    if (p1 == 0)
    {
        pid1 = getpid();
        
        pid2 = fork();
        if (pid2 == 0)
        {
            pid3 = fork();
            if (pid3 == 0)
            {
                for (size_t i = 0; i < 1000000; i++){ }          
            }
            
        }else{

        }

        wait(NULL);

        
    }
    
    

    
    return (0);
}
