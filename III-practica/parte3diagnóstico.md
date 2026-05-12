# Parte 3 Diagnóstico

Al ejecutar memcheck vemos que se presentan los siguientes problemas.

    LEAK SUMMARY:
    ==12042==    definitely lost: 48 bytes in 4 blocks
    ==12042==    indirectly lost: 0 bytes in 0 blocks
    ==12042==      possibly lost: 0 bytes in 0 blocks
    ==12042==    still reachable: 0 bytes in 0 blocks
    ==12042==         suppressed: 0 bytes in 0 blocks

Se observa que hay 48 bytes en 4 bloques definitivamente perdidos.

Verificando mas a fondo la información proporcionada por memcheck, se ve que el error está en la línea 42

    ==12042== 48 bytes in 4 blocks are definitely lost in loss record 1 of 1
    ==12042==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==12042==    by 0x10934D: main (clima.c:42)


El problema estaba sucediendo debido a que en cada iteración del for se estaba reservando la memoria para la variable y no se estaba liberando en ningún momento.

La solución fue sacar el malloc del for y liberar esa memoria al final del programa.


Al resolver eso y ejecutar Helgrind tenemos en varias ocasiones el siguiente error.

    ==14527== Possible data race during write of size 4 at 0x70B0488 by thread #1
    ==14527== Locks held: none
    ==14527==    at 0x10937B: main (climaModificado.c:46)
    ==14527==  Address 0x70b0488 is 8 bytes inside a block of size 12 alloc'd
    ==14527==    at 0x48488A8: malloc (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
    ==14527==    by 0x109344: main (climaModificado.c:41)
    ==14527==  Block was alloc'd by thread #1

El cual esta sucediendo debido a que en una iteración del for se envía el struct a un hilo, pero en la siguiente se modifica el struct.

El siguiente error tambien aparece varias veces.

    ==15943== Possible data race during read of size 4 at 0x10C020 by thread #3
    ==15943== Locks held: none
    ==15943==    at 0x10926A: analizar_temperaturas (climaModificado.c:26)
    ==15943==    by 0x4854B7A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
    ==15943==    by 0x4911AA3: start_thread (pthread_create.c:447)
    ==15943==    by 0x499EA63: clone (clone.S:100)
    ==15943==  Address 0x10c020 is 0 bytes inside data symbol "alertas_calor"

Este sucede debido a que se está modificando la variable alertas_calor simultáneamente en los 4 hilos.

El error de el struct en las iteraciones se resolvió creando un arreglo de structs para pasarle uno a cada hilo, y al final despues de resolver los hilos se van liberando uno por uno.

El error de la variable alertas_calor siendo modificada simultaneamente se resuelve creando una variable para retornarla con la cantidad de sumas a realizar y sumandolas fuera de los hilos.

realizando estas correcciones, al correr valgrind con memcheck y helgrind no nos presenta ningun error

    ==28581== All heap blocks were freed -- no leaks are possible
    ==28587== ERROR SUMMARY: 0 errors from 0 contexts 

