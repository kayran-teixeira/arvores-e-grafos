#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct No{
    char palavra[100];
    struct No* proximo;
} No;

No* lista = NULL;
int tamanho_lista = 0;

No* inserir_final(No* cabeca, const char* palavra) {
    No* novoNo = (No*)malloc(sizeof(No));

    if (novoNo == NULL) {
        printf("Erro de alocação de memória");
        return cabeca;
    }

    strcpy(novoNo->palavra, palavra);
    novoNo->proximo = NULL;

    if (cabeca == NULL) {
        tamanho_lista++;
        return novoNo;
    }

    No* temp = cabeca;
    while (temp->proximo != NULL){
        temp = temp->proximo;
    }

    temp->proximo = novoNo;
    tamanho_lista++;
    return cabeca;
}

No* remover_posicao(No* cabeca, int posicao) {
    if (cabeca == NULL || posicao < 0 || posicao >= tamanho_lista) {
        printf("Posição inválida ou lista vazia.\n");
        return cabeca;
    }

    No* atual = cabeca;
    No* anterior = NULL;

    if (posicao == 0) {
        cabeca = cabeca->proximo;
        free(atual->palavra);
        free(atual);
        tamanho_lista--;
        return cabeca;
    }

    for (int i = 0; i < posicao; i++) {
        anterior = atual;
        atual = atual->proximo;
    }

    anterior->proximo = atual->proximo;
    free(atual->palavra);
    free(atual);
    tamanho_lista--;

    return cabeca;
}


void exibir_lista(No* cabeca) {
    if (cabeca == NULL) {
        printf("Lista está vazia!\n");
        return;
    }

    printf("Elementos da lista:\n");
    while (cabeca != NULL) {
        printf("- %s\n", cabeca->palavra);
        cabeca = cabeca->proximo;
    }
}


void liberar_lista(No* cabeca) {
    No* temp;
    while (cabeca != NULL) {
        temp = cabeca;
        cabeca = cabeca->proximo;
        free(temp->palavra);
        free(temp);
    }
}


int main() {
    int opcao, posicao;
    char palavra[MAX];

    do {
        printf("1. Inserir string\n");
        printf("2. Exibir lista\n");
        printf("3. Remover string por posição\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Digite a string: ");
                fgets(palavra, MAX, stdin);
                palavra[strcspn(palavra, "\n")] = '\0';
                lista = inserir_final(lista, palavra);
                break;
            case 2:
                exibir_lista(lista);
                break;
            case 3:
                printf("Digite a posição do elemento a remover (0 a %d): ", tamanho_lista - 1);
                scanf("%d", &posicao);
                getchar();
                lista = remover_posicao(lista, posicao);
                break;
            case 4:
                liberar_lista(lista);
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 4);

    return 0;
}