#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    char letra;
    struct No* proximo;
} No;

No* lista = NULL;
int tamanho_lista = 0;

No* inserir_final(No* cabeca, char letra_no) {
    No* novoNo= (No*)malloc(sizeof(No));

    if (novoNo == NULL) {
        printf("Erro de alocação de memória");
        return cabeca;
    }

    novoNo->letra = letra_no;
    novoNo->proximo = NULL;

    if (cabeca == NULL) {
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
        free(atual);
        tamanho_lista--;
        return cabeca;
    }

    for (int i = 0; i < posicao; i++) {
        anterior = atual;
        atual = atual->proximo;
    }

    anterior->proximo = atual->proximo;
    free(atual);
    tamanho_lista--;

    return cabeca;
}
