#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5

typedef struct {
    int id;
    char nome[50];
    int quantidade;
    float preco;
} Produto;

void ler_influencer(Produto *i) {
    printf("Digite ID do produto: ");
    scanf("%d", &i->id);
    getchar();
    
    printf("Digite o nome do produto: ");
    fgets(i->nome, sizeof(i->nome), stdin);
    i->nome[strcspn(i->nome, "\n")] = '\0';

    printf("Digite a quantidade de produtos em estoque: ");
    scanf("%d", &i->quantidade);
    getchar();

    printf("Digite o valor do produto: ");
    scanf("%f", &i->preco);
    getchar();
}


void exibir_influencers(Produto vetor[], int n) {
    printf("\nInfluencers ordenados por seguidores:\n");
    for(int j = 0; j < n; j++){
        printf("ID: %d, Nome: %s, Quantidade em estoque: %d, Valor: %f\n", vetor[j].id ,vetor[j].nome, vetor[j].quantidade, vetor[j].preco);
    }
}


void BubbleSort(Influencer vetor[], int n) {
    int i, j;
    Influencer temp;

    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (vetor[j].seguidores < vetor[j+1].seguidores){
                temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;
            }
        }
    }
}



int main() {
    Influencer influencers[MAX];
    printf("PROGRAMA DE ADIÇÃO E ORDENAÇÃO DE INFLUENCERS POR NÚMERO DE SEGUIDORES\n\n");

    for(int j = 0; j < MAX; j++) {
        printf("Adição do influencer: %d\n", j+1);
        ler_influencer(&influencers[j]);
        printf("\n");
    }

    BubbleSort(influencers, MAX);
    exibir_influencers(influencers, MAX);

    return 0;
}