#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAMANHO 10000

int lista[TAMANHO];
int comparacoes = 0, movimentacoes = 0;


void InsertionSort(int vetor[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = vetor[i];
        j = i - 1;
        
        // Move os elementos de arr[0..i-1] que são maiores que a chave
        while (j >= 0 && vetor[j] > key) {
            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        vetor[j + 1] = key;
    }
}


int main() {
    int i;
    srand(time(0));

    for (int i = 0; i < TAMANHO; i++) {
        lista[i] = rand();
    }
    printf("Lista original: ");

    for (i = 0; i < TAMANHO; i++) {
        printf("%d ", lista[i]);
    }
    printf("\n\n");
    clock_t inicio = clock();
    InsertionSort(lista, TAMANHO);
    clock_t fim = clock();
    printf("Lista ordenada de forma crescente:");
    
    for (i = 0; i < TAMANHO; i++) {
        printf("%d ", lista[i]);
    }
    printf("\n\n");
    printf("Número de comparações: %d\n", comparacoes);
    printf("Número de movimentações: %d\n", movimentacoes);
    double tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    printf("Tempo de execução: %.2f milissegundos\n", tempo_execucao);
    
    return 0;
}