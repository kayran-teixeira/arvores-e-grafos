#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 2

typedef struct {
    char **data;
    int size;
    int capacity;
} StringList;

// Função para inicializar a lista dinâmica
void initList(StringList *list) {
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    list->data = (char **)malloc(list->capacity * sizeof(char *));
    if (list->data == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        exit(EXIT_FAILURE);
    }
}

// Função para redimensionar a lista
void resizeList(StringList *list) {
    list->capacity *= 2;
    list->data = (char **)realloc(list->data, list->capacity * sizeof(char *));
    if (list->data == NULL) {
        fprintf(stderr, "Erro ao realocar memória\n");
        exit(EXIT_FAILURE);
    }
}

// Função para adicionar uma string à lista
void addString(StringList *list, const char *str) {
    if (list->size == list->capacity) {
        resizeList(list);
    }
    list->data[list->size] = strdup(str);
    if (list->data[list->size] == NULL) {
        fprintf(stderr, "Erro ao alocar memória para string\n");
        exit(EXIT_FAILURE);
    }
    list->size++;
}

// Função para remover uma string da lista
void removeString(StringList *list, const char *str) {
    for (int i = 0; i < list->size; i++) {
        if (strcmp(list->data[i], str) == 0) {
            free(list->data[i]);
            for (int j = i; j < list->size - 1; j++) {
                list->data[j] = list->data[j + 1];
            }
            list->size--;
            return;
        }
    }
    printf("String não encontrada.\n");
}

// Função para buscar uma string na lista
int searchString(StringList *list, const char *str) {
    for (int i = 0; i < list->size; i++) {
        if (strcmp(list->data[i], str) == 0) {
            return i;
        }
    }
    return -1;
}

// Função para liberar memória
void freeList(StringList *list) {
    for (int i = 0; i < list->size; i++) {
        free(list->data[i]);
    }
    free(list->data);
}

// Função principal para testes
int main() {
    StringList list;
    initList(&list);
    
    addString(&list, "Olá");
    addString(&list, "Mundo");
    addString(&list, "Teste");
    
    printf("Lista de strings:\n");
    for (int i = 0; i < list.size; i++) {
        printf("%s\n", list.data[i]);
    }
    
    printf("Removendo 'Mundo'...\n");
    removeString(&list, "Mundo");
    
    printf("Lista após remoção:\n");
    for (int i = 0; i < list.size; i++) {
        printf("%s\n", list.data[i]);
    }
    
    printf("Buscando 'Teste': Índice %d\n", searchString(&list, "Teste"));
    
    freeList(&list);
    return 0;
}