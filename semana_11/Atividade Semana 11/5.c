#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarefa {
    char descricao[100];
    long dataVencimento;
    char prioridade[10];
    struct Tarefa* esq;
    struct Tarefa* dir;
} Tarefa;

Tarefa* novaTarefa(char descricao[], long dataVencimento, char prioridade[]) {
    Tarefa* t = (Tarefa*)malloc(sizeof(Tarefa));
    strcpy(t->descricao, descricao);
    t->dataVencimento = dataVencimento;
    strcpy(t->prioridade, prioridade);
    t->esq = t->dir = NULL;
    return t;
}

Tarefa* inserir(Tarefa* raiz, char descricao[], long dataVencimento, char prioridade[]) {
    if (raiz == NULL) return novaTarefa(descricao, dataVencimento, prioridade);
    if (dataVencimento < raiz->dataVencimento)
        raiz->esq = inserir(raiz->esq, descricao, dataVencimento, prioridade);
    else
        raiz->dir = inserir(raiz->dir, descricao, dataVencimento, prioridade);
    return raiz;
}

Tarefa* menorValor(Tarefa* raiz) {
    Tarefa* atual = raiz;
    while (atual && atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

Tarefa* remover(Tarefa* raiz, long dataVencimento) {
    if (raiz == NULL) return raiz;
    if (dataVencimento < raiz->dataVencimento)
        raiz->esq = remover(raiz->esq, dataVencimento);
    else if (dataVencimento > raiz->dataVencimento)
        raiz->dir = remover(raiz->dir, dataVencimento);
    else {
        if (raiz->esq == NULL) {
            Tarefa* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            Tarefa* temp = raiz->esq;
            free(raiz);
            return temp;
        }
        Tarefa* temp = menorValor(raiz->dir);
        strcpy(raiz->descricao, temp->descricao);
        raiz->dataVencimento = temp->dataVencimento;
        strcpy(raiz->prioridade, temp->prioridade);
        raiz->dir = remover(raiz->dir, temp->dataVencimento);
    }
    return raiz;
}

void atualizarTarefa(Tarefa* raiz, long dataVencimento) {
    if (raiz == NULL) return;
    if (dataVencimento < raiz->dataVencimento)
        atualizarTarefa(raiz->esq, dataVencimento);
    else if (dataVencimento > raiz->dataVencimento)
        atualizarTarefa(raiz->dir, dataVencimento);
    else {
        char novaDescricao[100];
        char novaPrioridade[10];
        printf("Nova descrição: ");
        getchar();
        fgets(novaDescricao, 100, stdin);
        novaDescricao[strcspn(novaDescricao, "\n")] = '\0';
        printf("Nova prioridade (baixa/media/alta): ");
        fgets(novaPrioridade, 10, stdin);
        novaPrioridade[strcspn(novaPrioridade, "\n")] = '\0';
        strcpy(raiz->descricao, novaDescricao);
        strcpy(raiz->prioridade, novaPrioridade);
        printf("Tarefa atualizada com sucesso.\n");
    }
}

void listarTarefas(Tarefa* raiz) {
    if (raiz == NULL) return;
    listarTarefas(raiz->esq);
    printf("Data: %ld | Prioridade: %s | Descrição: %s\n", raiz->dataVencimento, raiz->prioridade, raiz->descricao);
    listarTarefas(raiz->dir);
}

void filtrarPorPrioridade(Tarefa* raiz, char prioridade[]) {
    if (raiz == NULL) return;
    filtrarPorPrioridade(raiz->esq, prioridade);
    if (strcmp(raiz->prioridade, prioridade) == 0)
        printf("Data: %ld | Prioridade: %s | Descrição: %s\n", raiz->dataVencimento, raiz->prioridade, raiz->descricao);
    filtrarPorPrioridade(raiz->dir, prioridade);
}

void notificarVencidas(Tarefa* raiz, long hoje) {
    if (raiz == NULL) return;
    notificarVencidas(raiz->esq, hoje);
    if (raiz->dataVencimento < hoje)
        printf("TAREFA VENCIDA! Data: %ld | Prioridade: %s | Descrição: %s\n", raiz->dataVencimento, raiz->prioridade, raiz->descricao);
    notificarVencidas(raiz->dir, hoje);
}

int main() {
    Tarefa* raiz = NULL;
    int opcao;

    do {
        printf("\n--- MENU DE TAREFAS ---\n");
        printf("1. Adicionar tarefa\n");
        printf("2. Remover tarefa\n");
        printf("3. Atualizar tarefa\n");
        printf("4. Listar todas as tarefas\n");
        printf("5. Filtrar por prioridade\n");
        printf("6. Notificar tarefas vencidas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            char desc[100], pri[10];
            long data;
            getchar();
            printf("Descrição: ");
            fgets(desc, 100, stdin);
            desc[strcspn(desc, "\n")] = '\0';
            printf("Data de vencimento (yyyymmddhhmm): ");
            scanf("%ld", &data);
            getchar();
            printf("Prioridade (baixa/media/alta): ");
            fgets(pri, 10, stdin);
            pri[strcspn(pri, "\n")] = '\0';
            raiz = inserir(raiz, desc, data, pri);
        } else if (opcao == 2) {
            long data;
            printf("Data de vencimento da tarefa a remover: ");
            scanf("%ld", &data);
            raiz = remover(raiz, data);
        } else if (opcao == 3) {
            long data;
            printf("Data da tarefa a atualizar: ");
            scanf("%ld", &data);
            atualizarTarefa(raiz, data);
        } else if (opcao == 4) {
            listarTarefas(raiz);
        } else if (opcao == 5) {
            char pri[10];
            getchar();
            printf("Prioridade a filtrar (baixa/media/alta): ");
            fgets(pri, 10, stdin);
            pri[strcspn(pri, "\n")] = '\0';
            filtrarPorPrioridade(raiz, pri);
        } else if (opcao == 6) {
            long hoje;
            printf("Digite a data atual (yyyymmddhhmm): ");
            scanf("%ld", &hoje);
            notificarVencidas(raiz, hoje);
        }

    } while (opcao != 0);

    return 0;
}