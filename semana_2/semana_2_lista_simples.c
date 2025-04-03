#include <stdio.h>
#define MAX_SIZE 10

int lista[MAX_SIZE];
int tamanho = 0;


int menu() {
	int resposta;
	printf("Digite 1 para adicionar números da lista\n");
	printf("Digite 2 para remover números da lista\n");
	printf("Digite 3 para buscar números na lista pelo �ndice\n");
	printf("Digite 4 para imprimir a lista\n");
	printf("Digite 0 para fechar o programa\n");
	printf("Digite a opção desejada, lembrando que o tamanho máximo da lista são de 10 elementos: ");
	scanf("%d", &resposta);
	printf("\n");
	return resposta;
}


void adicionar() {
	int numero;
	printf("Digite o número que deseja adicionar no índice %d: ", tamanho);
	scanf("%d", &numero);
	lista[tamanho++] = numero;
	printf("O número %d foi adicionado!\n\n", numero);
}


void remover() {
	int numero, elemento_lista;
	printf("Digite o índice do número que deseja remover: ");
	scanf("%d", &numero);
	
	if (numero >= 0 && numero < tamanho) {
		elemento_lista = lista[numero];
		lista[numero] = 0;
		printf("O elemento %d foi removido do índice %d e substituido por 0!\n\n", elemento_lista, numero);
	} else {
		printf("Índice inexistente, tente remover outro índice.\n\n");
	}
}


void buscar() {
	int numero;
	printf("Digite o índice do número que deseja buscar: ");
	scanf("%d", &numero);
	
	if (numero >= 0 && numero < tamanho) {
		printf("O número no índice %d é: %d\n\n", numero, lista[numero]);
	} else {
		printf("Índice inexistente, tente buscar por outro índice.\n\n");
	}
}


void imprimir_lista(int vetor[], int tamanho_lista) {
	if (tamanho_lista == 0) {
		printf("Lista vazia, tente adicionar elementos a lista antes de imprimir\n\n\n");
		return;
	}
	
	int i;
	printf("Lista: ");
	
	for (i = 0; i < tamanho_lista; i++) {
		printf("%d ", vetor[i]);
	}
	printf("\n\n");
}

	                  
int main() {
	int loop = 1;
	
	while(loop == 1) {
	
		switch(menu()) {
			case 1:
				adicionar();
				break;
			
			case 2:
				remover();
				break;
				
			case 3:
				buscar();
				break;
				
			case 4:
				imprimir_lista(lista, tamanho);
				break;
				
			case 0:
				printf("\nFechando programa...");
				loop = 0;
				break;
			
			default:
				printf("\nOpção inexistente, tente inserir outro número\n\n");
				break;
		}
	}
	
	return 0;
}
