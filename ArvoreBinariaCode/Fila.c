#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct No {
    int valor;
    struct No *esq;
    struct No *dir;
};

// Estrutura auxiliar de fila para travessia em nível:
struct Fila {
    struct No *no;
    struct Fila *prox;
};

// Funções auxiliares para fila
void enfileirar(struct Fila **inicio, struct Fila **fim, struct No *no) {
    struct Fila *novo = (struct Fila *)malloc(sizeof(struct Fila));
    novo->no = no;
    novo->prox = NULL;
    if (*fim) {
        (*fim)->prox = novo;
    } else {
        *inicio = novo;
    }
    *fim = novo;
}

struct No *desenfileirar(struct Fila **inicio, struct Fila **fim) {
    if (*inicio == NULL) return NULL;
    struct Fila *temp = *inicio;
    struct No *no = temp->no;
    *inicio = temp->prox;
    if (*inicio == NULL) {
        *fim = NULL;
    }
    free(temp);
    return no;
}

// Função para verificar se a árvore é completa:
bool ehCompleta(struct No *raiz) {
    if (raiz == NULL) return true;

    struct Fila *inicio = NULL, *fim = NULL;
    enfileirar(&inicio, &fim, raiz);

    bool encontrouNulo = false; // se encontrou um nó incompleto, não pode ter mais nós não-nulos depois

    while (inicio != NULL) {
        struct No *atual = desenfileirar(&inicio, &fim);

        if (atual->esq != NULL) {
            if (encontrouNulo) return false; 
            enfileirar(&inicio, &fim, atual->esq);
        } else {
            encontrouNulo = true; 
        }

        if (atual->dir != NULL) {
            if (encontrouNulo) return false;
            enfileirar(&inicio, &fim, atual->dir);
        } else {
            encontrouNulo = true;
        }
    }

    return true;
}
