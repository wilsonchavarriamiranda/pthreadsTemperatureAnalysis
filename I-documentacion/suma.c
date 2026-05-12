#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Struct para mover los datos hacia el hilo.
typedef struct {
    int valor_a;
    int valor_b;
} DatosEntrada;

// Calcula la suma de los dos elementos del struct.
void* calcular_suma(void* arg) {
    // Crea un puntero de tipo DatosEntrada igual a los valores agarrados en los argumentos.
    DatosEntrada* datos = (DatosEntrada*)arg;
    printf("Datos recibidos %d y %d. \n", datos->valor_a, datos->valor_b);
    // Crea la variable resultado_local y le asigna la suma de los dos datos de los tipos de datos.
    int resultado_local = datos->valor_a + datos->valor_b;
    // Crea un puntero del tamaño de un entero con el nombre valor retorno.
    int* valor_retorno = malloc(sizeof(int));
    // Le asigna el resultado al puntero creado antes.
    *valor_retorno = resultado_local;
    printf("Salida del hilo. \n");
    // Retorna el valor como puntero void.
    return (void*)valor_retorno;
}

// Main crea un hilo y lo manda a sumar 2 datos.
int main(void) {
    // Crea una variable para almacenar el hilo con el nombre de mi_hilo.
    pthread_t mi_hilo;
    // Crea los datos de entrada.
    DatosEntrada argumentos = {15, 25};
    // Crea el puntero que va a almacenar el resultado final.
    int* resultado_final;
    // Si falla retorna con el valor 1.
    // Ejecuta el hilo con la funcion calcular suma enviando los argumentos como struct.
    printf("Inicialización de creación del hilo. \n");
    if (pthread_create(&mi_hilo, NULL, calcular_suma, &argumentos) != 0) {
        printf("Hubo un error al crear el hilo. \n");
        return 1;
    }
    printf("Finalización de creación del hilo. \n");
    printf("Esperando a que el hilo termine. \n");
    // Toma el valor como puntero generico.
    pthread_join(mi_hilo, (void**)&resultado_final);
    printf("Hilo terminado, resultado obtenido: %d \n", *(int*)resultado_final);
    // Libera la memoria.
    free(resultado_final);

    // Retorna 0 si todo está correcto.
    return 0;
}