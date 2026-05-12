
 /* IMPORTANTE PARA LA COMPILACIÓN: gcc -g -Wall clima.c -lpthread -o clima 
 Necesitan agregar -g para que Valgrind de información necesaria para el laboratorio */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_LECTURAS 10000000
#define NUM_HILOS 4

float *temperaturas;
int alertas_calor = 0;

typedef struct {
    int id_hilo;
    int indice_inicio;
    int indice_fin;
} DatosRango;

void* analizar_temperaturas(void* arg) {
    DatosRango* datos = (DatosRango*)arg;
    
    int* retorno = malloc(sizeof(int));
    *retorno = 0;

    for (int i = datos->indice_inicio; i < datos->indice_fin; i++) {
        if (temperaturas[i] > 35.0f) {
            (*retorno)++;
        }
    }
    return (void*)retorno;
}

int main(void) {
    temperaturas = malloc(NUM_LECTURAS * sizeof(float));
    for (int i = 0; i < NUM_LECTURAS; i++) {
        temperaturas[i] = 30.0f + (float)(rand() % 10); 
    }

    pthread_t hilos[NUM_HILOS];

    printf("Iniciando análisis \n");

    // Se crea un arreglo de los structs para usar uno por hilo
    DatosRango* datos[NUM_HILOS];

    for (int i = 0; i < NUM_HILOS; i++) {
        datos[i] = malloc(sizeof(DatosRango));
        datos[i]->id_hilo = i;
        datos[i]->indice_inicio = i * (NUM_LECTURAS / NUM_HILOS);
        datos[i]->indice_fin = (i + 1) * (NUM_LECTURAS / NUM_HILOS);

        pthread_create(&hilos[i], NULL, analizar_temperaturas, datos[i]);
    }

    // variable para recibir la cantidad de sumas realizadas por el hilo, para despues sumarlas al total uno por uno
    int* contador;

    for (int i = 0; i < NUM_HILOS; i++) { //Noten que el join puede esperar todos los hilos en un for con el ID de cada uno.
        pthread_join(hilos[i], (void**)&contador);
        alertas_calor += *contador;
        // se liberan los structs y el contador
        free(contador);
        free(datos[i]);
    }

    printf("Análisis completo. Total de alertas de calor extremo: %d \n", alertas_calor);
    free(temperaturas);
    return 0;
}