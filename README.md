# Pthreads — Temperature Analysis Lab

Laboratory exploring concurrency, indeterminism, and thread 
debugging in C using POSIX threads (pthreads).

## Built with
- C
- Pthreads
- Valgrind (Memcheck and Helgrind)

## Project structure

### Part 1 — Thread documentation
Implementation of `calcular_suma.c`, a simple threaded program 
that calculates the sum of two values using a secondary thread. 
Includes full internal documentation, thread lifecycle logging, 
and error handling.

### Part 2 — Climate analysis
A concurrent program that analyzes 10 million temperature readings 
across 4 threads, counting how many exceed the extreme heat 
threshold of 35.0°C.

Two bugs were identified and fixed:
- Memory leak detected with Valgrind Memcheck
- Race condition on shared variable detected with Helgrind

## Compilation
```bash
gcc -g -Wall calcular_suma.c -lpthread -o calcular_suma
gcc -g -Wall clima.c -lpthread -o clima
```

## Debugging with Valgrind
```bash
# Memory check
valgrind --leak-check=full ./clima

# Race condition check
valgrind --tool=helgrind ./clima
```

## Author
- Wilson Chavarría Miranda - C22114