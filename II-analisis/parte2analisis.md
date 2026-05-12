# Análisis

Utilizando el helgrind se observan el siguiente problema en multiples ocasiones.

    Possible data race during write of size 8 at 0x10C010 by thread #3
    ==10082== Locks held: none
    ==10082==    at 0x109275: EscuadronDefensa (in /home/wilson/Documents/paralela/laboratorios/laboratorio1/indeterminismo)
    ==10082==    by 0x4854B7A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
    ==10082==    by 0x4911AA3: start_thread (pthread_create.c:447)
    ==10082==    by 0x499EA63: clone (clone.S:100)
    ==10082== 
    ==10082== This conflicts with a previous read of size 8 by thread #2
    ==10082== Locks held: 1, at address 0x10C040
    ==10082==    at 0x109301: Radar (in /home/wilson/Documents/paralela/laboratorios/laboratorio1/indeterminismo)
    ==10082==    by 0x4854B7A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
    ==10082==    by 0x4911AA3: start_thread (pthread_create.c:447)
    ==10082==    by 0x499EA63: clone (clone.S:100)
    ==10082==  Address 0x10c010 is 0 bytes inside data symbol "vida_Escudo"

En este caso en específico, el hilo 3 está tratando de modificar datos que el hilo 2 había previamente modificado.

Todas las veces que aparece este error, es la misma situación pero con hilos diferentes.

Al correrlo con el memcheck no hay ningun problema