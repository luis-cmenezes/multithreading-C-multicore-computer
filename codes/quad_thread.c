#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define SIZE 7000
#define NUM_THREADS 4

// Estrutura para armazenar os argumentos das threads
typedef struct {
    int start_row;
    int end_row;
} ThreadArgs;

// Matrizes globais
static int M1[SIZE][SIZE], M2[SIZE][SIZE], M3[SIZE][SIZE];

// Função executada por cada thread
void* multiply(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    int start_row = args->start_row;
    int end_row = args->end_row;

    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                // Cada thread atualiza sua parte correspondente de M3
                M3[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    pthread_t threads[NUM_THREADS];
    ThreadArgs thread_args[NUM_THREADS];
    struct timespec start_time, end_time;
    double execution_time;

    if (atoi(argv[2]) == 0){
        printf("\n\nIniciando execução sem afinidade com 4 Threads número %s",argv[1]);
    }
    else{
        printf("\n\nIniciando execução com afinidade com 4 Threads número %s",argv[1]);
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

    clock_gettime(CLOCK_REALTIME, &start_time);

    // Criar as threads e atribuir a cada uma a responsabilidade de calcular uma parte de M3
    for (int i = 0; i < NUM_THREADS; i++) {
        int start_row = i * (SIZE / NUM_THREADS);
        int end_row = (i + 1) * (SIZE / NUM_THREADS);

        thread_args[i].start_row = start_row;
        thread_args[i].end_row = end_row;

        pthread_create(&threads[i], NULL, multiply, (void*)&thread_args[i]);
    }

    // Aguardar a finalização das threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
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

    FILE* file = fopen("/home/kirlin/multithreading-C-multicore-computer/results/resultado_quad_thread.txt", "a");
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
