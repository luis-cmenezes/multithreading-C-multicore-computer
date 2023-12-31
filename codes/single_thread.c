#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 7000

int main(int argc, char *argv[]) {
    static int M1[SIZE][SIZE], M2[SIZE][SIZE], M3[SIZE][SIZE];
    struct timespec start_time, end_time;
    double execution_time;

    if (atoi(argv[2]) == 0){
        printf("\n\nIniciando execução sem afinidade com 1 Thread número %s",argv[1]);
    }
    else{
        printf("\n\nIniciando execução com afinidade com 1 Thread número %s",argv[1]);
    }
    
    printf("\n");
    
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

    // Multiplicação
    clock_gettime(CLOCK_REALTIME, &start_time);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                M3[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }

    clock_gettime(CLOCK_REALTIME, &end_time);
    execution_time = (end_time.tv_sec - start_time.tv_sec) +
                     (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    printf("\nElementos da matriz resultante (M3) para checagem:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", M3[i][j]);
        }
        printf("\n");
    }

    // Salvar o tempo levado
    FILE* file = fopen("/home/kirlin/multithreading-C-multicore-computer/results/resultado_single_thread.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    printf("Tempo levado: %.5f segundos\n", execution_time);
    if (atoi(argv[2]) == 0){
        fprintf(file, "Execução sem afinidade %s: %.5f segundos\n", argv[1], execution_time);
    }
    else{
        fprintf(file, "Execução com afinidade %s: %.5f segundos\n", argv[1], execution_time);
    }
    fclose(file);
    
    return 0;
}
