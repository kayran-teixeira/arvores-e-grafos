#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#define TAMANHO 10000

int lista[TAMANHO];
int comparacoes = 0, movimentacoes = 0;


void BubbleSort(int vetor[], int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) { // looping para verificar se a lista foi percorrida
        for (j = 0; j < n-i-1; j++) { // lopping percorre ate antes do último elemento não odernado, assim garantindo a flutuação do último elemento ate o final
            comparacoes++;
            if (vetor[j] > vetor[j+1]){ // condicional para verificar o elemento atual com o próximo elemento
                temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;
                movimentacoes += 3; // numero de trocas feitas após o termino do looping
            }
        }
    }
}


int main() {
    setlocale(LC_ALL, "portuguese");
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
    BubbleSort(lista, TAMANHO);
    clock_t fim = clock();
    printf("Lista ordenada de forma crescente:");
    
    for (i = 0; i < TAMANHO; i++) {
        printf("%d ", lista[i]);
    }
    printf("\n\n");
    printf("Número de comparações: %d\n", comparacoes);
    printf("Número de movimentações: %d\n", movimentacoes);
    double tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f segundos\n", tempo_execucao);
    
    return 0;
}