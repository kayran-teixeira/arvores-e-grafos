#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAMANHO 10000

int lista[TAMANHO];
int comparacoes = 0, movimentacoes = 0;


void SelectionSort(int vetor[], int n) {
    int i, j, min_idx, temp;
    for (i = 0; i < n-1; i++) { // looping para percorrer todo o vetor
        min_idx = i; // posição i recebendo o menor valor restante do vetor a cada interação
        for (j = i + 1; j < n; j++){ // comparando o primeiro elemento do vetor restante com o resto dos elementos do mesmo vetor
            comparacoes++;
            if (vetor[j] < vetor[min_idx]){ // verificando se o primeiro elemento da lista desordenada é menor que o menor vetor eoncontrado
                min_idx = j;
            }
        }
        temp = vetor[min_idx];
        vetor[min_idx] = vetor[i];
        vetor[i] = temp;
        movimentacoes += 3; // número de trocas entre o elemento de valor mínimo e o elemento da interação
    }
}


int main() {
    int i;
    srand(time(0));

    for (i = 0; i < TAMANHO; i++) {
        lista[i] = rand();
    }
    printf("Lista original: ");
    
    for (i = 0; i < TAMANHO; i++) {
        printf("%d ", lista[i]);
    }
    printf("\n\n");
    clock_t inicio = clock();
    SelectionSort(lista, TAMANHO);
    clock_t fim = clock();
    printf("Lista organizada de forma crescente: ");
    
    for (i = 0; i < TAMANHO; i++) {
        printf("%d ", lista[i]);
    }
    printf("\n");
    printf("Número de comparações: %d\n", comparacoes);
    printf("Número de movimentações: %d\n", movimentacoes);
    double tempo_execucao = ((double)(inicio - fim)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f\n", tempo_execucao);

    return 0;
}