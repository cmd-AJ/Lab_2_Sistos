#include <stdio.h>
#include <time.h>

int main() {
    int million = 1000000;
    clock_t tiempo;
    clock_t tiempo2;
    double tiempocompleto;

    tiempo = clock();   
    for (int i = 0; i < million; i++) { }
    for (int i = 0; i < million; i++) { }
    for (int i = 0; i < million; i++) { }
    tiempo2 = clock();   

    tiempocompleto = (double)(tiempo2 - tiempo) / CLOCKS_PER_SEC;
    printf("Tiempo: %f segundos\n", tiempocompleto);

    return 0;
}
