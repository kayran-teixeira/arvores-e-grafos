#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5

typedef struct {
    char nome[50];
    int seguidores;
} Influencer;

void ler_influencer(Influencer *i) {
    printf("Digite o nome do influencer: ");
    fgets(i->nome, sizeof(i->nome), stdin);
    i->nome[strcspn(i->nome, "\n")] = '\0';

    printf("Digite o número de seguidores: ");
    scanf("%d", &i->seguidores);
    getchar();
}


void exibir_influencers(Influencer vetor[], int n) {
    printf("\nInfluencers ordenados por seguidores:\n");
    for(int j = 0; j < n; j++){
        printf("Nome: %s, seguidores: %d\n", vetor[j].nome, vetor[j].seguidores);
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