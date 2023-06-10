#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE 10000
#define NUM_THREADS 4

int M1[SIZE][SIZE], M2[SIZE][SIZE], M3[SIZE][SIZE];
pthread_mutex_t mutex;

// Estrutura de dados para os argumentos da thread
typedef struct {
    int thread_id;
} ThreadData;

// Função executada pelas threads
void* multiplyMatrix(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int thread_id = data->thread_id;

    int start_row = (SIZE / NUM_THREADS) * thread_id;
    int end_row = (SIZE / NUM_THREADS) * (thread_id + 1);

    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                pthread_mutex_lock(&mutex);
                M3[i][j] += M1[i][k] * M2[k][j];
                pthread_mutex_unlock(&mutex);
            }
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);

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

    // Medir o tempo de execução com 4 threads
    clock_t start_time = clock();

    // Criar as threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].thread_id = i;
        pthread_create(&threads[i], NULL, multiplyMatrix, (void*)&thread_data[i]);
    }

    // Aguardar a conclusão das threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end_time = clock();
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Salvar o tempo levado em um arquivo
    FILE* file = fopen("resultado_threads.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fprintf(file, "Tempo levado com 4 threads: %.3f segundos\n", execution_time);

    fclose(file);

    // Imprimir o resultado (M3)
    printf("Matriz resultante (M3):\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", M3[i][j]);
        }
        printf("\n");
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
