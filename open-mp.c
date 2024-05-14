#include <stdio.h> 

#include <stdlib.h> 

#include <omp.h> 

  

int main(int argc, char *argv[]) { 

    unsigned short xi[3] = {1, 2, 3}; 

    unsigned long long count = 0; 

    long long i; 

    long long samples; 

    double x, y; 

    samples = 3000000; /*Valor por defecto*/ 

    if (argc > 1) /* Para su uso en línea de comandos */ 

        samples = atoll(argv[1]); 

  

    // Usar srand() para inicializar la semilla de generación de números aleatorios 

    srand(omp_get_wtime() * 1000); 

  

    #pragma omp parallel for private(x, y) reduction(+:count) 

    for (i = 0; i < samples; ++i) { 

        x = ((double)rand()) / ((double)RAND_MAX); // 0≤x≤1 

        y = ((double)rand()) / ((double)RAND_MAX); 

        if (x * x + y * y <= 1.0) { 

            ++count; 

        } 

    } 

  

    printf("Valor estimado de pi: %.7f\n", 4.0 * count / samples); 

  

    return 0; 

} 