#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produto {
    int id;
    char nome[50];
    int quantidade;
    float preco;
    struct Produto *esq, *dir;
} Produto;

Produto* novoProduto(int id, char nome[], int quantidade, float preco) {
    Produto* p = (Produto*)malloc(sizeof(Produto));
    p->id = id;
    strcpy(p->nome, nome);
    p->quantidade = quantidade;
    p->preco = preco;
    p->esq = p->dir = NULL;
    return p;
}


Produto* inserir(Produto* raiz, int id, char nome[], int quantidade, float preco) {
    if (raiz == NULL) return novoProduto(id, nome, quantidade, preco);

    if (id < raiz->id)
        raiz->esq = inserir(raiz->esq, id, nome, quantidade, preco);
    else if (id > raiz->id)
        raiz->dir = inserir(raiz->dir, id, nome, quantidade, preco);

    return raiz;
}

Produto* menorValor(Produto* raiz) {
    Produto* atual = raiz;
    while (atual && atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

Produto* remover(Produto* raiz, int id) {
    if (raiz == NULL) return raiz;

    if (id < raiz->id)
        raiz->esq = remover(raiz->esq, id);
    else if (id > raiz->id)
        raiz->dir = remover(raiz->dir, id);
    else {
        if (raiz->esq == NULL) {
            Produto* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            Produto* temp = raiz->esq;
            free(raiz);
            return temp;
        }

        Produto* temp = menorValor(raiz->dir);
        raiz->id = temp->id;
        strcpy(raiz->nome, temp->nome);
        raiz->quantidade = temp->quantidade;
        raiz->preco = temp->preco;
        raiz->dir = remover(raiz->dir, temp->id);
    }
    return raiz;
}

void atualizarEstoque(Produto* raiz, int id, int quantidadeVendida) {
    if (raiz == NULL) return;
    if (id < raiz->id)
        atualizarEstoque(raiz->esq, id, quantidadeVendida);
    else if (id > raiz->id)
        atualizarEstoque(raiz->dir, id, quantidadeVendida);
    else {
        if (raiz->quantidade >= quantidadeVendida) {
            raiz->quantidade -= quantidadeVendida;
            printf("Venda realizada. Estoque atualizado.\n");
        } else {
            printf("Estoque insuficiente.\n");
        }
    }
}

void listarBaixoEstoque(Produto* raiz, int limite) {
    if (raiz == NULL) return;
    listarBaixoEstoque(raiz->esq, limite);
    if (raiz->quantidade < limite)
        printf("ID: %d | Nome: %s | Quantidade: %d | Preço: %.2f\n",
               raiz->id, raiz->nome, raiz->quantidade, raiz->preco);
    listarBaixoEstoque(raiz->dir, limite);
}

void buscarPorPreco(Produto* raiz, float min, float max) {
    if (raiz == NULL) return;
    buscarPorPreco(raiz->esq, min, max);
    if (raiz->preco >= min && raiz->preco <= max)
        printf("ID: %d | Nome: %s | Quantidade: %d | Preço: %.2f\n",
               raiz->id, raiz->nome, raiz->quantidade, raiz->preco);
    buscarPorPreco(raiz->dir, min, max);
}

void lerProduto(int *id, char nome[], int *quantidade, float *preco) {
    printf("Digite ID do produto: ");
    scanf("%d", id);
    getchar();

    printf("Digite o nome do produto: ");
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Digite a quantidade em estoque: ");
    scanf("%d", quantidade);

    printf("Digite o preço do produto: ");
    scanf("%f", preco);
}

int main() {
    Produto* raiz = NULL;
    int opcao;

    do {
        printf("\n--- MENU ESTOQUE ---\n");
        printf("1. Adicionar produto\n");
        printf("2. Remover produto\n");
        printf("3. Atualizar estoque após venda\n");
        printf("4. Listar produtos com estoque baixo\n");
        printf("5. Buscar produtos por faixa de preço\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            int id, qtd;
            char nome[50];
            float preco;
            lerProduto(&id, nome, &qtd, &preco);
            raiz = inserir(raiz, id, nome, qtd, preco);
        } else if (opcao == 2) {
            int id;
            printf("Digite o ID do produto a ser removido: ");
            scanf("%d", &id);
            raiz = remover(raiz, id);
        } else if (opcao == 3) {
            int id, qtd;
            printf("Digite o ID do produto vendido: ");
            scanf("%d", &id);
            printf("Digite a quantidade vendida: ");
            scanf("%d", &qtd);
            atualizarEstoque(raiz, id, qtd);
        } else if (opcao == 4) {
            int limite;
            printf("Digite o limite de estoque: ");
            scanf("%d", &limite);
            listarBaixoEstoque(raiz, limite);
        } else if (opcao == 5) {
            float min, max;
            printf("Digite o preço mínimo: ");
            scanf("%f", &min);
            printf("Digite o preço máximo: ");
            scanf("%f", &max);
            buscarPorPreco(raiz, min, max);
        }

    } while (opcao != 0);

    return 0;
}