#include<stdio.h>
#include<stdlib.h>

struct No{
    int valor;
    struct No *dir;
    struct No *esq;
};

void insert(struct No **raiz, int valor){

    if(*raiz == NULL){
        *raiz = (struct No*)malloc(sizeof(struct No));

        if(*raiz != NULL){
            (*raiz)->valor = valor;
            (*raiz)->esq = NULL;
            (*raiz)->dir = NULL;
        }else{
            printf("ERROR : [%i] nao inserido, memoria insuficiente.\n", valor);
        }
    }else{
        if(valor < (*raiz)->valor){
            insert(&((*raiz)->esq), valor);
        }else if(valor > (*raiz)->valor){
            insert(&((*raiz)->dir), valor);
        }else{
            printf("Valor duplicado.\n");
        }
    }

}

int buscar(struct No **raiz, int busca){

    if(*raiz == NULL){
        printf("A arvore nao possui o Noh!\n");
        return 1;
    }else{
        if(busca == (*raiz)->valor){
            printf("Valor buscado [%i] encontrado!.\n", (*raiz)->valor);
            return 0;
        }else if(busca < (*raiz)->valor){
            return buscar(&(*raiz)->esq, busca);
        }else if(busca > (*raiz)->valor){
            return buscar(&(*raiz)->dir, busca);
        }
    }

}

void preOrder(struct No *raiz){
    if(raiz != NULL){
        printf("[%i] ", raiz->valor);
        preOrder(raiz->esq);
        preOrder(raiz->dir);
    }
}

void inOrder(struct No *raiz){
    if(raiz != NULL){
        inOrder(raiz->esq);
        printf("[%i] ", raiz->valor);
        inOrder(raiz->dir);
    }
}

void posOrder(struct No *raiz){
    if(raiz != NULL){
        posOrder(raiz->esq);
        posOrder(raiz->dir);
        printf("[%i] ", raiz->valor);

    }
}

int remover(struct No **raiz, int remocao) {
    if (*raiz == NULL) {
        printf("Valor [%i] não encontrado na árvore.\n", remocao);
        return 1;
    }
    if (remocao < (*raiz)->valor) {
        return remover(&((*raiz)->esq), remocao);
    } else if (remocao > (*raiz)->valor) {
        return remover(&((*raiz)->dir), remocao);
    } else {
        struct No *temp = *raiz;
        if (temp->esq == NULL && temp->dir == NULL) {
            free(temp);
            *raiz = NULL;
        } else if (temp->esq == NULL) {
            *raiz = temp->dir;
            free(temp);
        } else if (temp->dir == NULL) {
            *raiz = temp->esq;
            free(temp);
        } else {
            struct No *aux = temp->dir;
            struct No *paiAux = temp;
            while (aux->esq != NULL) {
                paiAux = aux;
                aux = aux->esq;
            }
            temp->valor = aux->valor;
            if (paiAux->esq == aux) {
                paiAux->esq = aux->dir;
            } else {
                paiAux->dir = aux->dir;
            }
            free(aux);
        }
        printf("Valor [%i] removido.\n", remocao);
        return 0;
    }

}

void liberarMemoriaArvore(struct No *raiz) {
    if (raiz != NULL) {
        liberarMemoriaArvore(raiz->esq);
        liberarMemoriaArvore(raiz->dir);
        free(raiz);
    }
}

int main(void){

    int valor, busca, remocao, opcao = -1;
    struct No *raiz = NULL;

    while(opcao != 0){
        printf("\n");
        printf(" [1] > Inserir <\n");
        printf(" [2] > buscar <\n");
        printf(" [3] > preOrder <\n");
        printf(" [4] > inOrder <\n");
        printf(" [5] > posOrder <\n");
        printf(" [6] > Remover < \n");
        printf(" [0] > EXIT <\n");

        printf("Informe a opcao: ");
        scanf("%i", &opcao);

        switch(opcao){
            case 1:
                printf("Informe um valor para o no: ");
                scanf("%i", &valor);
                insert(&raiz, valor);
                break;
            case 2:
                printf("Informe o valor para busca: ");
                scanf("%i", &busca);
                buscar(&raiz, busca);
                break;
            case 3:
                printf(" >> PreOrder <<\n");
                preOrder(raiz);
                break;
            case 4:
                printf(" >> InOrder << \n");
                inOrder(raiz);
                break;
            case 5:
                printf(" >> PosOrder << \n");
                posOrder(raiz);
                break;
            case 6:
                printf("Informe o valor para a remocao: ");
                scanf("%i", &remocao);
                remover(&raiz, remocao);
                break;
            case 0:
                liberarMemoriaArvore(raiz);
                break;
            default:
                printf("Informe uma opcao valida!.\n");
                break;
            
        }
    }

    free(raiz);

}