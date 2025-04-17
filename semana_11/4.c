#include <stdio.h>
#include <stdlib.h>

typedef struct Sensor {
    long timestamp;
    float valor;
    int idSensor;
    struct Sensor* esq;
    struct Sensor* dir;
} Sensor;

Sensor* novaLeitura(long timestamp, float valor, int idSensor) {
    Sensor* s = (Sensor*)malloc(sizeof(Sensor));
    s->timestamp = timestamp;
    s->valor = valor;
    s->idSensor = idSensor;
    s->esq = s->dir = NULL;
    return s;
}

Sensor* inserir(Sensor* raiz, long timestamp, float valor, int idSensor) {
    if (raiz == NULL) return novaLeitura(timestamp, valor, idSensor);
    if (timestamp < raiz->timestamp)
        raiz->esq = inserir(raiz->esq, timestamp, valor, idSensor);
    else
        raiz->dir = inserir(raiz->dir, timestamp, valor, idSensor);
    return raiz;
}

void buscarIntervalo(Sensor* raiz, long inicio, long fim) {
    if (raiz == NULL) return;
    if (raiz->timestamp >= inicio)
        buscarIntervalo(raiz->esq, inicio, fim);
    if (raiz->timestamp >= inicio && raiz->timestamp <= fim)
        printf("Timestamp: %ld | Sensor: %d | Valor: %.2f\n",
               raiz->timestamp, raiz->idSensor, raiz->valor);
    if (raiz->timestamp <= fim)
        buscarIntervalo(raiz->dir, inicio, fim);
}

void calcularMedia(Sensor* raiz, long inicio, long fim, float* soma, int* cont) {
    if (raiz == NULL) return;
    if (raiz->timestamp >= inicio)
        calcularMedia(raiz->esq, inicio, fim, soma, cont);
    if (raiz->timestamp >= inicio && raiz->timestamp <= fim) {
        *soma += raiz->valor;
        (*cont)++;
    }
    if (raiz->timestamp <= fim)
        calcularMedia(raiz->dir, inicio, fim, soma, cont);
}

void detectarAnomalias(Sensor* raiz, float minEsperado, float maxEsperado) {
    if (raiz == NULL) return;
    detectarAnomalias(raiz->esq, minEsperado, maxEsperado);
    if (raiz->valor < minEsperado || raiz->valor > maxEsperado)
        printf("Anomalia! Timestamp: %ld | Sensor: %d | Valor: %.2f\n",
               raiz->timestamp, raiz->idSensor, raiz->valor);
    detectarAnomalias(raiz->dir, minEsperado, maxEsperado);
}

int main() {
    Sensor* raiz = NULL;
    int opcao;

    do {
        printf("\n--- MENU MONITORAMENTO IoT ---\n");
        printf("1. Inserir nova leitura\n");
        printf("2. Buscar leituras por intervalo de tempo\n");
        printf("3. Calcular média de leituras no intervalo\n");
        printf("4. Detectar leituras anômalas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            long ts;
            float val;
            int id;
            printf("Timestamp (yyyymmddhhmm): ");
            scanf("%ld", &ts);
            printf("Valor da leitura: ");
            scanf("%f", &val);
            printf("ID do sensor: ");
            scanf("%d", &id);
            raiz = inserir(raiz, ts, val, id);
        } else if (opcao == 2) {
            long ini, fim;
            printf("Intervalo inicial (yyyymmddhhmm): ");
            scanf("%ld", &ini);
            printf("Intervalo final (yyyymmddhhmm): ");
            scanf("%ld", &fim);
            buscarIntervalo(raiz, ini, fim);
        } else if (opcao == 3) {
            long ini, fim;
            float soma = 0;
            int cont = 0;
            printf("Intervalo inicial (yyyymmddhhmm): ");
            scanf("%ld", &ini);
            printf("Intervalo final (yyyymmddhhmm): ");
            scanf("%ld", &fim);
            calcularMedia(raiz, ini, fim, &soma, &cont);
            if (cont > 0)
                printf("Média: %.2f\n", soma / cont);
            else
                printf("Nenhuma leitura no intervalo informado.\n");
        } else if (opcao == 4) {
            float min, max;
            printf("Valor mínimo esperado: ");
            scanf("%f", &min);
            printf("Valor máximo esperado: ");
            scanf("%f", &max);
            detectarAnomalias(raiz, min, max);
        }

    } while (opcao != 0);

    return 0;
}