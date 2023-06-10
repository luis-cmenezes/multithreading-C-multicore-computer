#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

int main() {
    int M1[SIZE][SIZE], M2[SIZE][SIZE], M3[SIZE][SIZE];

    // Inicializar M1 e M2 com valor 1
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            M1[i][j] = 1;
            M2[i][j] = 1;
        }
    }

    // Inicializar M3 com valor 0
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            M3[i][j] = 0;
        }
    }

    
    // Multiplicação Single-Thread
    clock_t start_time = clock();

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                M3[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }

    clock_t end_time = clock();
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Matriz resultante (M3):\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", M3[i][j]);
        }
        printf("\n");
    }

    // Imprimir e salvar o resultado (M3) e o tempo levado
    FILE* file = fopen("resultado_single_thread.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    printf("Tempo levado: %.5f segundos\n", execution_time);
    fprintf(file, "Tempo levado: %.5f segundos\n", execution_time);

    fclose(file);
    
    return 0;
}
