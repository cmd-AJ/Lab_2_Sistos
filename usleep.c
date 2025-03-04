#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <unistd.h>

int main() {

    

    printf("Creando proceso...\n");
    clock_t time1;
    clock_t time2;
    time1 = clock();
    // usleep(500000);  // Pausar por 500 ms
    int pid = fork();

    time2 = clock();

    if (pid == 0) {
        printf("Soy el proceso hijo\n");
    } else {
        printf("Soy el proceso padre\n");
    }

    printf("TIEMPO: %ld \n", (time2 - time1)/CLOCKS_PER_SEC);

    return 0;
}