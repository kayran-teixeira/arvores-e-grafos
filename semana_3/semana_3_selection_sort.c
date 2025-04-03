#include <stdio.h>
#include <stdlib.h>
#define TAMANHO 100

int vetor1[TAMANHO];
int comparacoes1 = 0, movimentacoes1 = 0;

void preencherVetorAleatorio(int vetor[], int tamanho, int min, int max) {
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = rand() % (max - min + 1) + min;
    }
}


void selectionSort(int arr[], int n) {
	int i, j, min_idx, temp;
	for (i = 0; i < n-1; i++) {
		min_idx = i;
		for (j = i+1; j < n; j++) {
			comparacoes1++;
			if (arr[j] < arr[min_idx]) {
				min_idx = j;
			}		
		}
		temp = arr[min_idx];
		arr[min_idx] = arr[i];
		arr[i] = temp;
		movimentacoes1 += 3;
	}
}


int main(){
	preencherVetorAleatorio(vetor1, TAMANHO, 1, 5000);
	
	printf("Vetor 1 preenchido com números aleatorios:\n");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d ", vetor1[i]);
    }
    
	printf("\n\n");
    selectionSort(vetor1, TAMANHO);
    
    printf("Vetor 1 ordenado utilizando o Selection Sort:\n");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d ", vetor1[i]);
    }
    
    printf("\n\n");
    printf("Número de comparações: %d\n", comparacoes1);
    printf("Número de movimentações: %d\n", movimentacoes1);
    
    return 0;
}