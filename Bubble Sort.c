#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define TAMANHO 100

int vetor2[TAMANHO];
int comparacoes2 = 0, movimentacoes2 = 0;

void preencherVetorAleatorio(int vetor[], int tamanho, int min, int max) {
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = rand() % (max - min + 1) + min;
    }
}


void bubbleSort(int arr[], int n) {
	int i, j, temp;
	for (i = 0; i < n-1; i++) {
		for (j = 0; j < n-i-1; j++) {
			comparacoes2++;
			if (arr[j] > arr[j+1]) {
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				movimentacoes2 += 3;
			}	
		}
	}
}


int main(){
	
	setlocale(LC_ALL, "portuguese");
	
	preencherVetorAleatorio(vetor2, TAMANHO, 1, 5000);
	
	printf("Vetor 2 preenchido com n�meros aleat�rios:\n");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d ", vetor2[i]);
    }
    
	printf("\n\n");
    bubbleSort(vetor2, TAMANHO);
    
    printf("Vetor 2 ordenado utilizando o Bubble Sort:\n");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d ", vetor2[i]);
    }
    
    printf("\n\n");
    printf("N�mero de compara��es: %d\n", comparacoes2);
    printf("N�mero de movimenta��es: %d\n", movimentacoes2);
    
    return 0;
}