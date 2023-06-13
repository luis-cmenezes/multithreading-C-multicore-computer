#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000

int main(int argc, char *argv[]) {
    static int M1[SIZE][SIZE], M2[SIZE][SIZE], M3[SIZE][SIZE];
    int count = 1;

    printf("\n\nIniciando execução número %s", argv[1]);

    // Inicializar M1 e M2 com valor 1
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            M1[i][j] = 1;
            M2[i][j] = 1;
        }
    }

    printf("\nFinalizou o preenchimento de M1 e M2.");

    // Inicializar M3 com valor 0
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            M3[i][j] = 0;
        }
    }

    printf("\nFinalizou o preenchimento de M3.");

    // Multiplicação Single-Thread
    clock_t start_time = clock();

    for (int i = 0; i < SIZE; i++) {
        //Contador de progresso
        //printf("\n%.3f", 100.0*count/(SIZE*SIZE));
        
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                M3[i][j] += M1[i][k] * M2[k][j];
            }
            count++;
        }
    }

    clock_t end_time = clock();
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("\nAlguns elementos da matriz resultante (M3) para checagem do resultado:\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", M3[i][j]);
        }
        printf("\n");
    }

    // Imprimir e salvar o resultado (M3) e o tempo levado
    FILE* file = fopen("/home/kirlin/multithreading-C-multicore-computer/src/results/resultado_single_thread.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    printf("Tempo levado: %.5f segundos\n", execution_time);
    fprintf(file, "Execução %s: %.5f segundos\n", argv[1], execution_time);

    fclose(file);
    
    return 0;
}
