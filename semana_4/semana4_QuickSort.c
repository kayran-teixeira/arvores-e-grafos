#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAMANHO 10000

int lista[TAMANHO];
int comparacoes = 0, movimentacoes = 0;


int partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low + 1;
    int j = high;

    while (1) {
        while (arr[i] <= pivot && i <= high) i++;
        while (arr[j] > pivot && j >= low) j--;
        if (i >= j) break;
        // Troca os elementos
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    // Troca o pivô para a posição final
    arr[low] = arr[j];
    arr[j] = pivot;
    
    return j;
}


void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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
    quickSort(lista, 0, TAMANHO - 1);
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