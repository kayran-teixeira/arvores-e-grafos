#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct No {
    int dado;
    struct No* proximo;
} No;

No* lista = NULL;
int tamanho = 0;

No* inserir_final(No* cabeca, int valor_no) {
    No* novoNo = (No*)malloc(sizeof(No));
    
    if (novoNo == NULL) {
    printf("Erro de alocação de memória");
    return cabeca;
    }

    novoNo->dado = valor_no;
    novoNo->proximo = NULL;
  
    if (cabeca == NULL) {
        return novoNo;
    }

    No* temp = cabeca;
    while (temp->proximo != NULL) {
        temp = temp->proximo;
    }
    
    temp->proximo = novoNo;
    tamanho++;
    return cabeca;
}


No* remover(No* cabeca, int valor_no) {
    if (indice < 0 || indice >= tamanho) {
        printf("Índice inválido! \n");
        return cabeca;
    }

    No* temp = cabeca;
    No* anterior = NULL
}


int menu() {
	int resposta;
	printf("Digite 1 para adicionar n�meros da lista\n");
	printf("Digite 2 para remover n�meros da lista\n");
	printf("Digite 3 para buscar n�meros na lista pelo �ndice\n");
	printf("Digite 4 para imprimir a lista\n");
	printf("Digite 0 para fechar o programa\n");
	printf("Digite a op��o desejada, lembrando que o tamanho m�ximo da lista s�o de 10 elementos: ");
	scanf("%d", &resposta);
	printf("\n");
	return resposta;
}


void adicionar() { 
	int numero;
	printf("Digite o n�mero que deseja adicionar no �ndice %d: ", tamanho);
	scanf("%d", &numero);
	lista = inserir_final(lista, numero);
	printf("O n�mero %d foi adicionado!\n\n", numero);
}


void remover() {
	int numero, elemento_lista;
	printf("Digite o �ndice do n�mero que deseja remover: ");
	scanf("%d", &numero);
	
	if (numero >= 0 && numero < tamanho) {
		elemento_lista = lista[numero];
		lista[numero] = 0;
		printf("O elemento %d foi removido do �ndice %d e substituido por 0!\n\n", elemento_lista, numero);
	} else {
		printf("�ndice inexistente, tente remover outro �ndice.\n\n");
	}
}


void buscar() {
	int numero;
	printf("Digite o �ndice do n�mero que deseja buscar: ");
	scanf("%d", &numero);
	
	if (numero >= 0 && numero < tamanho) {
		printf("O n�mero no �ndice %d �: %d\n\n", numero, lista[numero]);
	} else {
		printf("�ndice inexistente, tente buscar por outro �ndice.\n\n");
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
	setlocale(LC_ALL, "Portuguese");
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
				printf("\nOp��o inexistente, tente inserir outro n�mero\n\n");
				break;
		}
	}
	
	return 0;
}