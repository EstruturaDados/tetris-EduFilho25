#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3

typedef struct {
    char nome;
    int id;
} Peca;

int proximoId = 0;

Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = proximoId;
    proximoId++;
    return p;
}

void exibirEstado(Peca fila[], int inicioFila, int qtdFila,
                  Peca pilha[], int topoPilha) {
    int i;
    int idx;

    printf("\nEstado atual:\n\n");

    printf("Fila de pecas\t");
    for (i = 0; i < qtdFila; i++) {
        idx = (inicioFila + i) % MAX_FILA;
        printf("[%c %d] ", fila[idx].nome, fila[idx].id);
    }
    if (qtdFila == 0) {
        printf("(vazia)");
    }
    printf("\n");

    printf("Pilha de reserva\t(Topo -> base): ");
    if (topoPilha < 0) {
        printf("(vazia)");
    } else {
        for (i = topoPilha; i >= 0; i--) {
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);
        }
    }
    printf("\n");
}

int main() {
    Peca fila[MAX_FILA];
    Peca pilha[MAX_PILHA];

    int inicioFila = 0;
    int fimFila = 0;
    int qtdFila = 0;
    int topoPilha = -1;

    int i;
    int opcao;

    srand(time(NULL));

    for (i = 0; i < MAX_FILA; i++) {
        fila[fimFila] = gerarPeca();
        fimFila = (fimFila + 1) % MAX_FILA;
        qtdFila++;
    }

    do {
        exibirEstado(fila, inicioFila, qtdFila, pilha, topoPilha);

        printf("\nOpcoes:\n");
        printf("1 - Jogar peca da frente da fila\n");
        printf("2 - Enviar peca da fila para a pilha de reserva\n");
        printf("3 - Usar peca da pilha de reserva\n");
        printf("4 - Trocar peca da frente da fila com o topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com as 3 pecas da pilha\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            if (qtdFila == 0) {
                printf("Fila vazia, nao ha peca para jogar.\n");
            } else {
                Peca jogada = fila[inicioFila];
                inicioFila = (inicioFila + 1) % MAX_FILA;
                qtdFila--;
                printf("Peca jogada: [%c %d]\n", jogada.nome, jogada.id);

                if (qtdFila < MAX_FILA) {
                    fila[fimFila] = gerarPeca();
                    fimFila = (fimFila + 1) % MAX_FILA;
                    qtdFila++;
                }
            }

        } else if (opcao == 2) {
            if (qtdFila == 0) {
                printf("Fila vazia, nao ha peca para reservar.\n");
            } else if (topoPilha == MAX_PILHA - 1) {
                printf("Pilha cheia, nao ha espaco para reservar.\n");
            } else {
                Peca reservada = fila[inicioFila];
                inicioFila = (inicioFila + 1) % MAX_FILA;
                qtdFila--;

                topoPilha++;
                pilha[topoPilha] = reservada;
                printf("Peca enviada para a pilha: [%c %d]\n", reservada.nome, reservada.id);

                if (qtdFila < MAX_FILA) {
                    fila[fimFila] = gerarPeca();
                    fimFila = (fimFila + 1) % MAX_FILA;
                    qtdFila++;
                }
            }

        } else if (opcao == 3) {
            if (topoPilha < 0) {
                printf("Pilha vazia, nao ha peca reservada para usar.\n");
            } else {
                Peca usada = pilha[topoPilha];
                topoPilha--;
                printf("Peca reservada usada: [%c %d]\n", usada.nome, usada.id);
            }

        } else if (opcao == 4) {
            if (qtdFila == 0) {
                printf("Fila vazia, nao ha peca na frente.\n");
            } else if (topoPilha < 0) {
                printf("Pilha vazia, nao ha peca para trocar.\n");
            } else {
                Peca temp = fila[inicioFila];
                fila[inicioFila] = pilha[topoPilha];
                pilha[topoPilha] = temp;
                printf("Troca simples realizada entre fila e pilha.\n");
            }

        } else if (opcao == 5) {
            if (qtdFila < 3) {
                printf("Fila nao tem 3 pecas para trocar.\n");
            } else if (topoPilha < 2) {
                printf("Pilha nao tem 3 pecas para trocar.\n");
            } else {
                int k;
                for (k = 0; k < 3; k++) {
                    int idxFila = (inicioFila + k) % MAX_FILA;
                    int idxPilha = topoPilha - k;
                    Peca temp = fila[idxFila];
                    fila[idxFila] = pilha[idxPilha];
                    pilha[idxPilha] = temp;
                }
                printf("Troca multipla realizada entre as 3 primeiras da fila e as 3 da pilha.\n");
            }

        } else if (opcao == 0) {
            printf("Saindo...\n");
        } else {
            printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}
