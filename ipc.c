#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#define SHM_NAME "/shared_memory_ipc"
#define SHM_SIZE 4096  // Tamaño de la memoria compartida

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <número n> <carácter x>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);   // Convertir el argumento a entero
    char x = argv[2][0];     // Extraer el carácter de entrada

    int shm_fd;
    int is_creator = 0;
    
    // Intentar abrir la memoria compartida
    shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    
    if (shm_fd == -1) {
        // Si no existe, crearla
        shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
        if (shm_fd == -1) {
            perror("Error al abrir/crear la memoria compartida");
            exit(EXIT_FAILURE);
        }
        is_creator = 1;

        // Ajustar el tamaño de la memoria compartida
        if (ftruncate(shm_fd, SHM_SIZE) == -1) {
            perror("Error al establecer tamaño de memoria compartida");
            exit(EXIT_FAILURE);
        }
    }

    printf("Memoria compartida abierta con descriptor: %d\n", shm_fd);

    // Pequeña pausa para permitir que la otra instancia sincronice
    usleep(500000);  // 500 ms de espera

    // Mapear la memoria compartida
    void *shm_ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("Error al mapear la memoria compartida");
        exit(EXIT_FAILURE);
    }

    // Crear un pipe para la comunicación entre padre e hijo
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("Error al crear pipe");
        exit(EXIT_FAILURE);
    }

    // Crear el proceso hijo
    pid_t pid = fork();
    if (pid < 0) {
        perror("Error al hacer fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Proceso hijo
        close(pipefd[1]);  // Cierra el extremo de escritura del pipe

        char buffer[1];
        int index = 0;
        char *shm_char_ptr = (char *)shm_ptr;

        while (read(pipefd[0], buffer, 1) > 0) {
            shm_char_ptr[index++] = buffer[0];  // Escribir en la memoria compartida
        }

        close(pipefd[0]);  // Cierra el extremo de lectura del pipe
        printf("Proceso hijo: escritura en memoria compartida finalizada.\n");
        exit(EXIT_SUCCESS);
    } else {  // Proceso padre
        close(pipefd[0]);  // Cierra el extremo de lectura del pipe

        // Pausa antes de enviar datos al hijo para asegurarse de que esté listo
        usleep(100000);  // 100 ms de espera

        for (int i = 1; i <= SHM_SIZE; i++) {
            if (i % n == 0) {
                write(pipefd[1], &x, 1);  // Enviar carácter al hijo
            }
        }

        usleep(100000); 

        close(pipefd[1]);  

        // Esperar al hijo
        wait(NULL);

        usleep(200000);
        // Mostrar el contenido de la memoria compartida
        printf("Contenido de la memoria compartida:\n");
        printf("%s\n", (char *)shm_ptr);

        // Desmapear y eliminar la memoria compartida solo si fue creada en esta instancia
        munmap(shm_ptr, SHM_SIZE);
        close(shm_fd);
        if (is_creator) {
            shm_unlink(SHM_NAME);
        }

        printf("\nProceso padre finalizado y memoria compartida liberada.\n");
    }

    return 0;
}
