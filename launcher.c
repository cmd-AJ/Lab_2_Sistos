#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pid = fork();

    if (pid == -1) {
        perror("Error en fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        execl("./ipc", "ipc", "3", "a", NULL);
        perror("Error en execl");
        exit(EXIT_FAILURE);
    } else {
        int pid2 = fork();
        if (pid2 == -1) {
            perror("Error en segundo fork");
            exit(EXIT_FAILURE);
        }

        if (pid2 == 0) {
            execl("./ipc", "ipc", "5", "b", NULL);
            perror("Error en execl");
            exit(EXIT_FAILURE);
        }

        wait(NULL);
        wait(NULL);
    }

    return 0;
}
