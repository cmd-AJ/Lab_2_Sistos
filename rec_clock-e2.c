#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, pid3;
    clock_t time1, time2;
    time1 = clock();
    int p1 = fork();

    if (p1 == 0) {  
        int p2 = fork();
        if (p2 == 0) {
            int p3 = fork();
            if (p3 == 0) {
                for (int i = 0; i < 1000000; i++) {}
            } else {
                for (int i = 0; i < 1000000; i++) {}
                wait(NULL);
            }
        } else {
            for (int i = 0; i < 1000000; i++) {}
            wait(NULL);
        }
    } else {
        time2 = clock();
        printf("Tiempo transcurrido: %lf \n", (double)(time2 - time1)/CLOCKS_PER_SEC);
    }


    return 0;
}