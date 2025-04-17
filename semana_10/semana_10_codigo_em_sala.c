#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore
typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

// Função para inserir um valor na árvore
No* inserir(No* raiz, int valor) {
    if (raiz == NULL) {
        No* novo = (No*)malloc(sizeof(No));
        novo->valor = valor;
        novo->esq = novo->dir = NULL;
        return novo;
    }

    // Verificar para onde o novo nó será inserido
    if (valor < raiz->valor) {
        raiz->esq = inserir(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = inserir(raiz->dir, valor);
    }

    return raiz; // Quando o valor for igual ele é ignorado se tiver dois valores duplicados.
}

// Função para buscar um valor na árvore
No* busca(No* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) {
        return raiz;
    }

    if (valor < raiz->valor) {
        return busca(raiz->esq, valor);
    } else {
        return busca(raiz->dir, valor);
    }
}

// Função para auxiliar a encontrar o menor valor de uma subárvore
No* menorValor(No* raiz) {
    No* atual = raiz;
    while (atual && atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}

// Função para remover um valor
No* remover(No* raiz, int valor) {
    if (raiz == NULL)
        return NULL;

    if (valor < raiz->valor) {
        raiz->esq = remover(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = remover(raiz->dir, valor);
    } else {
        // Caso 1: nó sem filhos
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }
        // Caso 2: nó tem um filho
        else if (raiz->esq == NULL) {
            No* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            No* temp = raiz->esq;
            free(raiz);
            return temp;
        }
        // Caso 3: nó tem dois filhos
        No* temp = menorValor(raiz->dir);
        raiz->valor = temp->valor;
        raiz->dir = remover(raiz->dir, temp->valor);
    }

    return raiz;
}

// Função para imprimir a árvore em ordem (percurso in-order transversal)
void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("%d ", raiz->valor);
        emOrdem(raiz->dir);
    }
}

int main() {
    No* raiz = NULL;
    int valorbusca;

    // Inserindo valores
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 2);
    raiz = inserir(raiz, 7);
    raiz = inserir(raiz, 12);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 22);

    printf("Imprimindo os valores da Árvore Binária: ");
    emOrdem(raiz);
    printf("\n");

    // Buscando um valor
    valorbusca = 7;
    No* encontrado = busca(raiz, valorbusca);
    if (encontrado)
        printf("\nValor %d encontrado na árvore.", valorbusca);
    else
        printf("\nValor %d não encontrado na árvore.", valorbusca);

    // Removendo valor
    raiz = remover(raiz, 10);
    printf("\nÁrvore após a remoção do valor 10:\n");
    emOrdem(raiz);
    printf("\n");

    return 0;
}