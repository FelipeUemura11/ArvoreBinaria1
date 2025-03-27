#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

struct No{
    int valor;
    struct No *esq;
    struct No *dir;
};

struct FilaLarg {
    struct No *no;
    struct FilaLarg *prox;
};

void enfileirar(struct FilaLarg **inicio, struct FilaLarg **fim, struct No *no) {
    struct FilaLarg *novo = (struct FilaLarg *)malloc(sizeof(struct FilaLarg));
    novo->no = no;
    novo->prox = NULL;
    if (*fim) {
        (*fim)->prox = novo;
    } else {
        *inicio = novo;
    }
    *fim = novo;
}

struct No *desenfileirar(struct FilaLarg **inicio, struct FilaLarg **fim) {
    if (*inicio == NULL) return NULL;
    struct FilaLarg *temp = *inicio;
    struct No *no = temp->no;
    *inicio = temp->prox;
    if (*inicio == NULL) {
        *fim = NULL;
    }
    free(temp);
    return no;
}

int arvoreCompleta(struct No *raiz) {
    if (raiz == NULL) {
        return 1;
    }

    struct FilaLarg *inicio = NULL, *fim = NULL;
    enfileirar(&inicio, &fim, raiz);
    bool encontrouNulo = false;

    while (inicio != NULL) {
        struct No *atual = desenfileirar(&inicio, &fim);

        if (atual->esq != NULL) {
            if(encontrouNulo){
                return 0;
            }
            enfileirar(&inicio, &fim, atual->esq);
        } else {
            encontrouNulo = true;
        }

        if (atual->dir != NULL) {
            if (encontrouNulo) {
                return 0;
            }
            enfileirar(&inicio, &fim, atual->dir);
        } else {
            encontrouNulo = true;
        }
    }
    return 1;
}

void adicionarNo(struct No **raiz, int valor){
    if(*raiz == NULL){
        *raiz = (struct No*)malloc(sizeof(struct No));

        if(*raiz != NULL){
            (*raiz)->valor = valor;
            (*raiz)->esq = NULL;
            (*raiz)->dir = NULL;
        }else{
            printf("ERROR : nao foi possivel alocar memoria...\n");
        }
    }else{
        if(valor < (*raiz)->valor){
            adicionarNo(&((*raiz)->esq), valor);
        }else if(valor > (*raiz)->valor){
            adicionarNo(&((*raiz)->dir), valor);
        }else{
            printf("Valor duplicado...\n");
        }
    }
}

int buscarNo(struct No **raiz, int busca){
    if(*raiz == NULL){
        printf("nao existe o  noh na arvore...\n");
        return 1;
    }else{
        if(busca == (*raiz)->valor){
            printf("O valor - %i foi encontrado na arvore!\n", (*raiz)->valor);
            return 0;
        }else if(busca < (*raiz)->valor){
            return buscarNo(&((*raiz)->esq), busca);
        }else if(busca > (*raiz)->valor){
            return buscarNo(&((*raiz)->dir), busca);
        }
    }
}

int removerNo(struct No **raiz, int remocao){

    if(*raiz == NULL){
        printf("Nao ah noh [%i] na arvore.\n", remocao);
        return 1;
    }

    if(remocao < (*raiz)->valor){
        return removerNo(&((*raiz)->esq), remocao);
    }else if(remocao > (*raiz)->valor){
        return removerNo(&((*raiz)->dir), remocao);
    }else{
        struct No *temp = *raiz;

        if(temp->esq == NULL && temp->dir == NULL){
            free(temp);
            *raiz = NULL;
        }else if(temp->esq == NULL){
            *raiz = temp->dir;
            free(temp);
        }else if(temp->dir == NULL){
            *raiz = temp->esq;
            free(temp);
        }else{
            // Encontrar o menor valor da subArvore direita
            struct No *aux = temp->dir;
            while(aux->esq != NULL){
                aux = aux->esq;
            }

            temp->valor = aux->valor;
            removerNo(&(temp->dir), aux->valor); // recursao para recomecar a leitura ate encontrar o valor

            
        }
        printf("Valor [%i] removido.\n", remocao);
        return 0;
    }

}

int alturaArvore(struct No **raiz){

    if(*raiz == NULL){
        return -1;
    }else{
        int alturaEsq = alturaArvore(&(*raiz)->esq);
        int alturaDir = alturaArvore(&(*raiz)->dir);

        if(alturaEsq > alturaDir){
            return alturaEsq + 1;
        }else{
            return alturaDir + 1;
        }
    }

}

void arvoreBalanceada(struct No **raiz){

    if(*raiz != NULL){
        int balancoEsq = alturaArvore(&(*raiz)->esq);
        int balancoDir = alturaArvore(&(*raiz)->dir);

        if(balancoEsq == balancoDir || balancoEsq == balancoDir + 1 || balancoEsq + 1 == balancoDir){
            printf("A Arvore esta balanceada!\n");
            printf("Esq: %i\n", balancoEsq);
            printf("Dir: %i\n", balancoDir);
        }else{
            printf("A Arvore esta desbalanceada!\n");
            printf("Esq: %i\n", balancoEsq);
            printf("Dir: %i\n", balancoDir);
        }
    }else{
        printf("Nao ha nos na arvore!\n");
    }

}

int totalDeNos(struct No **raiz){

    if(*raiz == NULL){
        printf("Sem nos na arvore!\n");
        return 0;
    }

    return 1 + totalDeNos(&(*raiz)->dir) + totalDeNos(&(*raiz)->esq);
}

int valorMinimo(struct No *raiz){
    if(raiz == NULL){
        printf("Sem nos na arvore!\n");
        return -1;
    }else{
        while(raiz->esq != NULL){
            raiz = raiz->esq;
        }
    }
    return raiz->valor;
}

int valorMaximo(struct No *raiz){
    if(raiz == NULL){
        printf("Sem nos na arvore!\n");
        return -1;
    }else{
        while(raiz->dir != NULL){
            raiz = raiz->dir;
        }
    }
    return raiz->valor;
}

void somaTotal(struct No *raiz, int *soma) {
    if (raiz != NULL) {
        *soma += raiz->valor;
        somaTotal(raiz->esq, soma);
        somaTotal(raiz->dir, soma);
    }
}

void liberarMemoriaArvore(struct No *raiz) {
    if (raiz != NULL) {
        liberarMemoriaArvore(raiz->esq);
        liberarMemoriaArvore(raiz->dir);
        free(raiz);
    }
}

int main(){

    struct No *raiz = NULL;
    int opcao = -1, valor = 0, busca = 0, remocao = 0, total = 0, soma = 0;

    while(opcao != 0){
        printf(" ==== Arvore Binaria ==== \n");
        printf(" [1] Adicionar \n");
        printf(" [2] Buscar \n");
        printf(" [3] Remover \n");
        printf(" [4] Altura \n");
        printf(" [5] Balanceamento \n");
        printf(" [6] Completa \n");
        printf(" [7] Total de nos \n");
        printf(" [8] Max/Min \n");
        printf(" [9] Soma total dos nos \n");
        printf(" [0] EXIT \n");

        printf("Escolha uma das opcoes a seguir: ");
        scanf("%i", &opcao);

        switch(opcao){
            case 1:
                printf("Adicione um valor ao noh: ");
                scanf("%i", &valor);
                adicionarNo(&raiz, valor);
                break;
            case 2:
                printf("Informe o valor que deseje buscar: ");
                scanf("%i", &busca);
                buscarNo(&raiz, busca);
                break;
            case 3:
                printf("Informe o valor para a remocao: ");
                scanf("%i", &remocao);
                removerNo(&raiz, remocao);
                break;
            case 4:
                printf("Altura da arvore: %i\n", alturaArvore(&raiz));
                break;
            case 5:
                arvoreBalanceada(&raiz);
                break;
            case 6:
                if(arvoreCompleta(raiz)) {
                    printf("A arvore eh completa!\n");
                } else {
                    printf("A arvore NAO eh completa.\n");
                }
                break;
            case 7:
                total = totalDeNos(&raiz);
                printf("Total de nos da arvore: %i\n", total);
                break;
            case 8:
                printf("Valor minimo da arvore: [%i]\n", valorMinimo(raiz));
                printf("Valor maximo da arvore: [%i]\n", valorMaximo(raiz));
                break;
            case 9:
                somaTotal(raiz, &soma);
                printf("Soma dos valores da arvore: %i\n", soma);
                break;
            case 0:
                printf("saindo...\n");
                liberarMemoriaArvore(raiz);
                break;
            default:
                printf("ERROR : Escolha uma opcao valida!\n");
                break;
        }
    }

    return 0;
}