#include <stdio.h>
#include <stdlib.h>

int menu() {
    int resposta;
    printf("ARMAZENAMENTO DE INTEIROS EM ÁRVORE BINÁRIA\n\n");
    printf("Digite 1 para adicionar números a árvore.\n");
    printf("Digite 2 para remover números da árvore.\n");
    printf("Digite 3 para buscar números da árvore.\n");
    printf("Digite 4 para imprimir a árvore no formato ordenado.\n");
    printf("Digite 5 para imprimir a lista no formato hierárquico.\n");
    printf("Digite 0 para sair do programa.\n");
    printf("Digite sua alternativa: ");
    scanf("%d", &resposta);
    printf("\n");
    return resposta;
}

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

// Função para imprimir a lista em forma hierárquica (Função auxiliada pelo chat GPT)
void imprimirHierarquico(No* raiz, int nivel) {
    if (raiz == NULL)
        return;

    // Imprime a subárvore da direita primeiro (vai aparecer no topo)
    imprimirHierarquico(raiz->dir, nivel + 1);

    // Imprime os espaços correspondentes ao nível do nó
    for (int i = 0; i < nivel; i++)
        printf("    "); // 4 espaços por nível

    // Imprime o valor do nó
    printf("%d\n", raiz->valor);

    // Imprime a subárvore da esquerda (vai aparecer embaixo)
    imprimirHierarquico(raiz->esq, nivel + 1);
}

int main() {
    No* raiz = NULL;
    while(1) {
        switch (menu()) {
            case 1: {
                // Código para o usuário inserir os números e chamar a função inserir
                int resp_loop_inserir;
                int resp_inserir;
                printf("Digite quantos números deseja inserir: ");
                scanf("%d", &resp_loop_inserir);
                for (int i = 0; i < resp_loop_inserir; i++) {
                    printf("Digite qual número deseja inserir: ");
                    scanf("%d", &resp_inserir);
                    raiz = inserir(raiz, resp_inserir);
                }
                printf("%d valores adicionados com sucesso!\n", resp_loop_inserir);
                printf("\n\n");
                break;
            }

            case 2: {
                // Código para o usuário inserir os números que deseja remover e chamar a função remover
                int resp_loop_remover;
                int resp_remover;
                printf("Digite quantos números deseja remover: ");
                scanf("%d", &resp_loop_remover);
                for (int i = 0; i < resp_loop_remover; i++) {
                    printf("Digite qual número deseja remover: ");
                    scanf("%d", &resp_remover);
                    raiz = remover(raiz, resp_remover);
                }
                printf("%d Valores removidos com sucesso!\n", resp_loop_remover);
                printf("\n\n");
                break;
            }

            case 3: {
                // Código para o usuário inserir os números para busca e chamar a função busca
                int valor_busca;
                printf("Digite o número que deseja buscar: ");
                scanf("%d", &valor_busca);
                No* buscar_no = busca(raiz, valor_busca);
                if (buscar_no) {
                    printf("Valor %d encontrado na árvore.\n", valor_busca);
                }

                else {
                    printf("Valor %d não encontrado na árvore.\n", valor_busca);
                }
                printf("\n\n");
                break;
            }

            case 4: {
                // Código para chamar a função emOrdem e imprimir a lista no formato ordenado
                printf("Imprimindo os valores da Árvore Binária: ");
                emOrdem(raiz);
                printf("\n\n\n");
                break;
            }

            case 5: {
                // Imprimir árvore em formato hierárquico
                printf("Árvore binária em formato hierárquico:\n\n");
                imprimirHierarquico(raiz, 0);
                printf("\n\n");
                break;
            }

            case 0: {
                // Caso para encerrar o while
                printf("Encerrando seu programa...");
                return 0;
            }

            default: {
                // Caso default para retornar ao looping e inserir outro um número válido
				printf("Opção inexistente, tente inserir outro número\n\n\n");
				break;
            }
        }
    }
}