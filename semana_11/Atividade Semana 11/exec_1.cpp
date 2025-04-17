#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// estrutura filme
typedef struct Filme {
    char titulo[100];
    char genero[50];
    int classificacao; 
    float pontuacao_media; 
    struct Filme *esquerda;
    struct Filme *direita;
} Filme;

// função para criar um novo nó de filme
Filme* criar_filme(char* titulo, char* genero, int classificacao, float pontuacao_media) {
    Filme* novo = (Filme*)malloc(sizeof(Filme));
    strcpy(novo->titulo, titulo);
    strcpy(novo->genero, genero);
    novo->classificacao = classificacao;
    novo->pontuacao_media = pontuacao_media;
    novo->esquerda = novo->direita = NULL;
    return novo;
}

// Função para inserir um novo filme na árvore binária de busca (ABB) ordenada pela pontuação média
Filme* inserir_filme(Filme* raiz, char* titulo, char* genero, int classificacao, float pontuacao_media) {
    if (raiz == NULL) {
        return criar_filme(titulo, genero, classificacao, pontuacao_media);
    }
    if (pontuacao_media < raiz->pontuacao_media) {
        raiz->esquerda = inserir_filme(raiz->esquerda, titulo, genero, classificacao, pontuacao_media);
    } else {
        raiz->direita = inserir_filme(raiz->direita, titulo, genero, classificacao, pontuacao_media);
    }
    return raiz;
}

// Função para buscar filmes por gênero
void buscar_por_genero(Filme* raiz, char* genero) {
    if (raiz == NULL) return;
    if (strstr(raiz->genero, genero) != NULL) {
        printf("Filme: %s | Gênero: %s | Classificação: %d | Pontuação: %.2f\n", raiz->titulo, raiz->genero, raiz->classificacao, raiz->pontuacao_media);
    }
    buscar_por_genero(raiz->esquerda, genero);
    buscar_por_genero(raiz->direita, genero);
}

// Função auxiliar para listar os top 5 filmes com maior pontuação
void listar_top_5(Filme* raiz, Filme* filmes[], int* count) {
    if (raiz == NULL || *count >= 5) return;
    listar_top_5(raiz->direita, filmes, count);
    if (*count < 5) {
        filmes[*count] = raiz;
        (*count)++;
    }
    listar_top_5(raiz->esquerda, filmes, count); 
}

// Função para listar os top 5 filmes
void listar_top_5_filmes(Filme* raiz) {
    Filme* filmes[5];
    int count = 0;
    listar_top_5(raiz, filmes, &count);
    printf("\nTop 5 Filmes com Maior Pontuação:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s - %.2f\n", i + 1, filmes[i]->titulo, filmes[i]->pontuacao_media);
    }
}

// Função para atualizar a pontuação de um filme
Filme* atualizar_pontuacao(Filme* raiz, char* titulo, float nova_pontuacao) {
    if (raiz == NULL) return NULL;

    if (strcmp(raiz->titulo, titulo) == 0) {
        raiz->pontuacao_media = nova_pontuacao;
        return raiz;
    }
    if (nova_pontuacao < raiz->pontuacao_media) {
        return atualizar_pontuacao(raiz->esquerda, titulo, nova_pontuacao);
    } else {
        return atualizar_pontuacao(raiz->direita, titulo, nova_pontuacao);
    }
}

// Função para imprimir a árvore
void imprimir_abb(Filme* raiz) {
    if (raiz == NULL) return;  // Caso base: se a árvore estiver vazia, não faz nada

    imprimir_abb(raiz->esquerda);  // Visita a subárvore esquerda
    printf("Filme: %s | Gênero: %s | Classificação: %d | Pontuação: %.2f\n", raiz->titulo, raiz->genero, raiz->classificacao, raiz->pontuacao_media);  // Visita o nó atual
    imprimir_abb(raiz->direita);  // Visita a subarvore direita
}


int main() {
	
	setlocale(LC_ALL, "Portuguese");
	
    Filme* raiz = NULL;
    int opcao;

    do {
        printf("\nSistema de Recomendação de Filmes\n");
        printf("1. Inserir novo filme\n");
        printf("2. Buscar filmes por gênero\n");
        printf("3. Listar os top 5 filmes com maior pontuação\n");
        printf("4. Atualizar a pontuação de um filme\n");
        printf("5. Exibir todos os filmes cadastrados\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  

        if (opcao == 1) {
            // Inserir novo filme
            char titulo[100], genero[50];
            int classificacao;
            float pontuacao_media;

            printf("Digite o título do filme: ");
            fgets(titulo, 100, stdin);
            titulo[strcspn(titulo, "\n")] = 0;  

            printf("Digite o gênero do filme: ");
            fgets(genero, 50, stdin);
            genero[strcspn(genero, "\n")] = 0;  

            printf("Digite a classificação indicativa do filme: ");
            scanf("%d", &classificacao);

            printf("Digite a pontuação média do filme: ");
            scanf("%f", &pontuacao_media);

            raiz = inserir_filme(raiz, titulo, genero, classificacao, pontuacao_media);
            printf("Filme inserido com sucesso!\n");
        } else if (opcao == 2) {
            // Buscar filmes por gênero
            char genero[50];
            printf("Digite o gênero para busca: ");
            getchar();  
            fgets(genero, 50, stdin);
            genero[strcspn(genero, "\n")] = 0;  
            buscar_por_genero(raiz, genero);
        } else if (opcao == 3) {
            // Lista os top 5 filmes
            listar_top_5_filmes(raiz);
        } else if (opcao == 4) {
            // Atualizar pontuação de um filme
            char titulo[100];
            float nova_pontuacao;

            printf("Digite o título do filme a ser atualizado: ");
            getchar(); 
            fgets(titulo, 100, stdin);
            titulo[strcspn(titulo, "\n")] = 0;  

            printf("Digite a nova pontuação média: ");
            scanf("%f", &nova_pontuacao);

            raiz = atualizar_pontuacao(raiz, titulo, nova_pontuacao);
            printf("Pontuação do filme atualizada!\n");
        } else if (opcao == 5) {
            // Exibir todos os filmes cadastrados
            printf("\nTodos os filmes cadastrados:\n");
            imprimir_abb(raiz);
        } else if (opcao == 0) {
            printf("Saindo...\n");
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

