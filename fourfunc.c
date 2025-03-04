#include <stdio.h>
#include <unistd.h>

int main() {
    int pid1, pid2, pid3, pid4;

    // Primer fork
    pid1 = fork();
    if (pid1 == 0) {
        printf("%d \n", (int)getpid());
    } else {
        // Segundo fork
        pid2 = fork();
        if (pid2 == 0) {
            printf("%d \n", (int)getpid());
        } else {
            // Tercer fork
            pid3 = fork();
            if (pid3 == 0) {
                printf("%d \n", (int)getpid());
            } else {
                // Cuarto fork
                pid4 = fork();
                if (pid4 == 0) {
                    printf("%d \n", (int)getpid());
                } else {
                    // Proceso padre original
                    printf("%d \n", (int)getpid());
                }
            }
        }
    }

    return 0;
}
