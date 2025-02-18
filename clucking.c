#include <stdio.h>
#include <time.h>


int main(){
    int million = 1000000;
    clock_t tiempo;
    clock_t tiempo2;
    double tiempocompleto;
    tiempo = clock();   

    for (size_t i = 0; i < million; i++){ }
    for (size_t i = 0; i < million; i++){ }
    for (size_t i = 0; i < million; i++){ }          

    tiempo2 = clock();   
    tiempocompleto = (double)( tiempo2-tiempo);

    printf( "Tiempo %f \n", tiempocompleto);

    return (0);
}
