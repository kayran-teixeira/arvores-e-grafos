#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura de Contato
typedef struct Contato {
    char nome[100];
    char telefone[20];
    char email[100];
    struct Contato *esquerda;
    struct Contato *direita;
} Contato;

// Função para criar um novo contato
Contato* criar_contato(char* nome, char* telefone, char* email) {
    Contato* novo = (Contato*)malloc(sizeof(Contato));
    strcpy(novo->nome, nome);
    strcpy(novo->telefone, telefone);
    strcpy(novo->email, email);
    novo->esquerda = novo->direita = NULL;
    return novo;
}

// Função para inserir um novo contato na árvore binária de busca
Contato* inserir_contato(Contato* raiz, char* nome, char* telefone, char* email) {
    if (raiz == NULL) {
        return criar_contato(nome, telefone, email);
    }
    if (strcmp(nome, raiz->nome) < 0) {
        raiz->esquerda = inserir_contato(raiz->esquerda, nome, telefone, email);
    } else {
        raiz->direita = inserir_contato(raiz->direita, nome, telefone, email);
    }
    return raiz;
}

// Função para buscar um contato pelo nome
Contato* buscar_contato(Contato* raiz, char* nome) {
    if (raiz == NULL || strcmp(raiz->nome, nome) == 0) {
        return raiz;
    }
    if (strcmp(nome, raiz->nome) < 0) {
        return buscar_contato(raiz->esquerda, nome);
    } else {
        return buscar_contato(raiz->direita, nome);
    }
}

// Função para listar todos os contatos em ordem alfabética (in-ordem)
void listar_contatos(Contato* raiz) {
    if (raiz != NULL) {
        listar_contatos(raiz->esquerda);
        printf("Nome: %s | Telefone: %s | Email: %s\n", raiz->nome, raiz->telefone, raiz->email);
        listar_contatos(raiz->direita);
    }
}

// Função de percurso em pré-ordem
void percurso_pre_ordem(Contato* raiz) {
    if (raiz != NULL) {
        printf("Nome: %s | Telefone: %s | Email: %s\n", raiz->nome, raiz->telefone, raiz->email);  
        percurso_pre_ordem(raiz->esquerda); 
        percurso_pre_ordem(raiz->direita);  
    }
}

// Função de autocompletar para nomes
void autocompletar(Contato* raiz, char* prefixo) {
    if (raiz != NULL) {
        if (strncmp(raiz->nome, prefixo, strlen(prefixo)) == 0) {
            printf("Nome: %s | Telefone: %s | Email: %s\n", raiz->nome, raiz->telefone, raiz->email);
        }
        autocompletar(raiz->esquerda, prefixo);
        autocompletar(raiz->direita, prefixo);
    }
}

// Função principal
int main() {
	
	setlocale(LC_ALL, "Portuguese");
	
    Contato* agenda = NULL;
    int opcao;
    char nome[100], telefone[20], email[100], prefixo[100];
    Contato* c;  

    do {
        printf("\nAgenda de Contatos Inteligente\n");
        printf("1. Inserir novo contato\n");
        printf("2. Buscar contato por nome\n");
        printf("3. Listar todos os contatos (em ordem alfabética)\n");
        printf("4. Percorrer a árvore em pré-ordem\n");
        printf("5. Autocompletar nome\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                printf("Digite o nome do contato: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;  
                printf("Digite o telefone do contato: ");
                fgets(telefone, sizeof(telefone), stdin);
                telefone[strcspn(telefone, "\n")] = 0;

                printf("Digite o e-mail do contato: ");
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")] = 0;

                agenda = inserir_contato(agenda, nome, telefone, email);
                printf("Contato inserido com sucesso!\n");
                break;

            case 2:
                printf("Digite o nome do contato para buscar: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                c = buscar_contato(agenda, nome);  
                if (c != NULL) {
                    printf("Nome: %s | Telefone: %s | Email: %s\n", c->nome, c->telefone, c->email);
                } else {
                    printf("Contato não encontrado.\n");
                }
                break;

            case 3:
                listar_contatos(agenda);
                break;

            case 4:
                printf("\nPercorrendo a árvore em pré-ordem:\n");
                percurso_pre_ordem(agenda);
                break;

            case 5:
                printf("Digite o prefixo para autocompletar: ");
                fgets(prefixo, sizeof(prefixo), stdin);
                prefixo[strcspn(prefixo, "\n")] = 0;

                autocompletar(agenda, prefixo);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

