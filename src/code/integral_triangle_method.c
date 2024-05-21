#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

double f( double x ) {
    return pow(x,3) / 3 + 4*x;
}

int main(int argc, char *argv[])
{
    double a = 0;     // lower bound of the interval
    double b = 1000;  // upper bound of the interval
    double h = 0.01;  // the width of each rectangle
    int ntest = 10;   // number of tests

    if ( argc == 2 && strcmp("-i", argv[1]) == 0 ) {
        printf("a: "); scanf(" %lf", &a);
        printf("b: "); scanf(" %lf", &b);
        printf("h: "); scanf(" %lf", &h);
        printf("ntest: "); scanf(" %d", &ntest);
    }

    if ( argc > 1 ) {
        a = atof(argv[1]);
        b = atof(argv[2]);
        h = atof(argv[3]);
        ntest = atoi(argv[4]);
    }

    printf("Nro Hilos, Tiempo Secuencial (ms), Tiempo Paralelo (ms), ");
    printf("Speedup, Eficiencia\n");

    double start, end;
    double seq_time, par_time;

    int num_threads = omp_get_max_threads();

    for ( int t = 1; t <= num_threads; ++t ) {
        seq_time = 0;
        for ( int n = 0; n < ntest; ++n ) {
            double sum = 0; // la integral de f
            start = omp_get_wtime();
            // CODIGO SECUENCIAL
            for ( double x = a; x <= b; x += h ) {
                sum += x * f(x);
            }
            // END
            end = omp_get_wtime();
            seq_time += end - start;
        }
        seq_time = seq_time / ntest;  // promedio de tiempo secuencial

        par_time = 0;
        for ( int n = 0; n < ntest; ++n ) {
            start = omp_get_wtime();
            // CODIGO EN PARALLELO
            double sum = 0; // la integral de f
            double mul = 1/h;
            double x;
            #pragma omp parallel for num_threads(t)
            // Como no podemos usar el tipo de datos 'double' en la estructura
            // 'for'. Nos ayudamos de un pequeño truco matematico ...
            for (int i = (int)(a*mul); i <= (int)(b*mul); i+=(int)(h*mul)) {
                x = i*h;
                sum += x * f(x);
            }
            // END
            end = omp_get_wtime();
            par_time += end - start;
        }
        par_time = par_time / ntest;  // promedio de tiempo parallelo

        // Results
        double speedup = seq_time / par_time;
        double efficiency = speedup / t;
        printf("%d, %lf, %lf, %lf, %lf\n",
                t, seq_time, par_time, speedup, efficiency
        );
    }

    return 0;
}

