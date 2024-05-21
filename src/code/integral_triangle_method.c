#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double f( double x ) {
    return pow(x,3) / 3 + 4*x;
}

int main(int argc, char *argv[])
{
    int ntest = 10; // number of tests
    double h = 0.1; // the width of each rectangle
    double a = 0;   // lower bound of the interval
    double b = 100; // upper bound of the interval

    printf("Nro Hilos, Tiempo Secuencial (ms), Tiempo Paralelo (ms), ");
    printf("Speedup, Eficiencia");
    printf("\n");

    double start, end;
    double seq_time, par_time;

    int num_threads = omp_get_max_threads();

    for ( int t = 0; t < num_threads; ++t ) {
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
        // promedio de tiempo secuencial
        seq_time = seq_time / ntest;

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
        // promedio de tiempo parallelo
        par_time = par_time / ntest;

        // Results
        double speedup = seq_time / par_time;
        double efficiency = speedup / t;
        printf("%d, %lf, %lf, %lf, %lf\n",
                t+1, seq_time, par_time, speedup, efficiency
        );
    }

    return 0;
}
