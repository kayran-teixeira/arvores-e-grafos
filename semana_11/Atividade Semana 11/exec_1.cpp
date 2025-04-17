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

// fun��o para criar um novo n� de filme
Filme* criar_filme(char* titulo, char* genero, int classificacao, float pontuacao_media) {
    Filme* novo = (Filme*)malloc(sizeof(Filme));
    strcpy(novo->titulo, titulo);
    strcpy(novo->genero, genero);
    novo->classificacao = classificacao;
    novo->pontuacao_media = pontuacao_media;
    novo->esquerda = novo->direita = NULL;
    return novo;
}

// Fun��o para inserir um novo filme na �rvore bin�ria de busca (ABB) ordenada pela pontua��o m�dia
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

// Fun��o para buscar filmes por g�nero
void buscar_por_genero(Filme* raiz, char* genero) {
    if (raiz == NULL) return;
    if (strstr(raiz->genero, genero) != NULL) {
        printf("Filme: %s | G�nero: %s | Classifica��o: %d | Pontua��o: %.2f\n", raiz->titulo, raiz->genero, raiz->classificacao, raiz->pontuacao_media);
    }
    buscar_por_genero(raiz->esquerda, genero);
    buscar_por_genero(raiz->direita, genero);
}

// Fun��o auxiliar para listar os top 5 filmes com maior pontua��o
void listar_top_5(Filme* raiz, Filme* filmes[], int* count) {
    if (raiz == NULL || *count >= 5) return;
    listar_top_5(raiz->direita, filmes, count);
    if (*count < 5) {
        filmes[*count] = raiz;
        (*count)++;
    }
    listar_top_5(raiz->esquerda, filmes, count); 
}

// Fun��o para listar os top 5 filmes
void listar_top_5_filmes(Filme* raiz) {
    Filme* filmes[5];
    int count = 0;
    listar_top_5(raiz, filmes, &count);
    printf("\nTop 5 Filmes com Maior Pontua��o:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s - %.2f\n", i + 1, filmes[i]->titulo, filmes[i]->pontuacao_media);
    }
}

// Fun��o para atualizar a pontua��o de um filme
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

// Fun��o para imprimir a �rvore
void imprimir_abb(Filme* raiz) {
    if (raiz == NULL) return;  // Caso base: se a �rvore estiver vazia, n�o faz nada

    imprimir_abb(raiz->esquerda);  // Visita a sub�rvore esquerda
    printf("Filme: %s | G�nero: %s | Classifica��o: %d | Pontua��o: %.2f\n", raiz->titulo, raiz->genero, raiz->classificacao, raiz->pontuacao_media);  // Visita o n� atual
    imprimir_abb(raiz->direita);  // Visita a subarvore direita
}


int main() {
	
	setlocale(LC_ALL, "Portuguese");
	
    Filme* raiz = NULL;
    int opcao;

    do {
        printf("\nSistema de Recomenda��o de Filmes\n");
        printf("1. Inserir novo filme\n");
        printf("2. Buscar filmes por g�nero\n");
        printf("3. Listar os top 5 filmes com maior pontua��o\n");
        printf("4. Atualizar a pontua��o de um filme\n");
        printf("5. Exibir todos os filmes cadastrados\n");
        printf("0. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);
        getchar();  

        if (opcao == 1) {
            // Inserir novo filme
            char titulo[100], genero[50];
            int classificacao;
            float pontuacao_media;

            printf("Digite o t�tulo do filme: ");
            fgets(titulo, 100, stdin);
            titulo[strcspn(titulo, "\n")] = 0;  

            printf("Digite o g�nero do filme: ");
            fgets(genero, 50, stdin);
            genero[strcspn(genero, "\n")] = 0;  

            printf("Digite a classifica��o indicativa do filme: ");
            scanf("%d", &classificacao);

            printf("Digite a pontua��o m�dia do filme: ");
            scanf("%f", &pontuacao_media);

            raiz = inserir_filme(raiz, titulo, genero, classificacao, pontuacao_media);
            printf("Filme inserido com sucesso!\n");
        } else if (opcao == 2) {
            // Buscar filmes por g�nero
            char genero[50];
            printf("Digite o g�nero para busca: ");
            getchar();  
            fgets(genero, 50, stdin);
            genero[strcspn(genero, "\n")] = 0;  
            buscar_por_genero(raiz, genero);
        } else if (opcao == 3) {
            // Lista os top 5 filmes
            listar_top_5_filmes(raiz);
        } else if (opcao == 4) {
            // Atualizar pontua��o de um filme
            char titulo[100];
            float nova_pontuacao;

            printf("Digite o t�tulo do filme a ser atualizado: ");
            getchar(); 
            fgets(titulo, 100, stdin);
            titulo[strcspn(titulo, "\n")] = 0;  

            printf("Digite a nova pontua��o m�dia: ");
            scanf("%f", &nova_pontuacao);

            raiz = atualizar_pontuacao(raiz, titulo, nova_pontuacao);
            printf("Pontua��o do filme atualizada!\n");
        } else if (opcao == 5) {
            // Exibir todos os filmes cadastrados
            printf("\nTodos os filmes cadastrados:\n");
            imprimir_abb(raiz);
        } else if (opcao == 0) {
            printf("Saindo...\n");
        } else {
            printf("Op��o inv�lida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

