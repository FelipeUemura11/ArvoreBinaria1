#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Produto {
    int id;
    char nome[45];
    float preco;
    int quantidade;
};

struct No {
    struct Produto produto;
    struct No *esq;
    struct No *dir;
};

void inserirProduto(struct No **raiz, struct Produto novoProduto) {
    if (*raiz == NULL) {
        *raiz = (struct No *)malloc(sizeof(struct No));
        if (*raiz != NULL) {
            (*raiz)->produto = novoProduto;
            (*raiz)->esq = NULL;
            (*raiz)->dir = NULL;
        } else {
            printf("ERROR: Insercao de dado na memoria invalida!\n");
        }
    } else {
        if (novoProduto.id < (*raiz)->produto.id) {
            inserirProduto(&(*raiz)->esq, novoProduto);
        } else if (novoProduto.id > (*raiz)->produto.id) {
            inserirProduto(&(*raiz)->dir, novoProduto);
        } else {
            printf("Produto duplicado.\n");
        }
    }
}

struct No *buscarProduto(struct No *raiz, int buscarId) {
    if (raiz == NULL || raiz->produto.id == buscarId) {
        return raiz;
    }
    if (buscarId < raiz->produto.id) {
        return buscarProduto(raiz->esq, buscarId);
    }
    return buscarProduto(raiz->dir, buscarId);
}

int removerProduto(struct No **raiz, int removerId) {
    if (*raiz == NULL) {
        printf("Nao ha noh [%i] na arvore!\n", removerId);
        return -1;
    }
    if (removerId < (*raiz)->produto.id) {
        return removerProduto(&((*raiz)->esq), removerId);
    } else if (removerId > (*raiz)->produto.id) {
        return removerProduto(&((*raiz)->dir), removerId);
    } else {
        struct No *temp = *raiz;
        if (temp->esq == NULL) {
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
            temp->produto = aux->produto;
            if (paiAux->esq == aux) {
                paiAux->esq = aux->dir;
            } else {
                paiAux->dir = aux->dir;
            }
            free(aux);
        }
        printf("Produto de id [%i] removido!\n", removerId);
        return 0;
    }
}

void inOrder(struct No *raiz) {
    if (raiz != NULL) {
        inOrder(raiz->esq);
        printf("[%i] ", raiz->produto.id);
        inOrder(raiz->dir);
    }
}

void alterarProduto(struct No **raiz, int produtoId){

    int novaQuant = 0;
    float novoPreco = 0.0;

    struct No *encontrado = buscarProduto(*raiz, produtoId);
    if(encontrado != NULL){
        printf("Informe o novo preco do produto %s: ", encontrado->produto.nome);
        scanf("%f", &novoPreco);
        encontrado->produto.preco = novoPreco;
        printf("Informe a nova quantidade do produto %s: ", encontrado->produto.nome);
        scanf("%i", &novaQuant);
        encontrado->produto.quantidade = novaQuant;

        printf("\n=============\n");
        printf("Produto Atualizado!\n");
        printf("Id: %i\n", encontrado->produto.id);
        printf("Nome: %s\n", encontrado->produto.nome);
        printf("Preco: %.2f\n", encontrado->produto.preco);
        printf("Quantidade: %i\n", encontrado->produto.quantidade);
        printf("=============\n");
    }else{
        printf("Produto nao encontrado...\n");
    }

}

void somaTotal(struct No *raiz, float *soma) {
    if (raiz != NULL) {
        float precoQuant = (raiz->produto.preco) * (raiz->produto.quantidade);
        *soma += precoQuant;
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

int main(void) {
    struct No *raiz = NULL;
    struct Produto produto;
    int opcao = -1, idBuscar, idRemover, idAlterar;
    float soma = 0.0;
    while (opcao != 0) {
        printf("\n == Produto == \n");
        printf(" [1] Inserir \n");
        printf(" [2] Buscar \n");
        printf(" [3] Remover \n");
        printf(" [4] inOrder \n");
        printf(" [5] Alterar \n");
        printf(" [6] SomaTotal(prec/quant) \n");
        printf(" [0] Sair \n");
        printf("Informe uma opcao: ");
        if (scanf("%i", &opcao) != 1) {
            printf("Entrada invalida!\n");
            while (getchar() != '\n');
            continue;
        }
        switch (opcao) {
            case 1:
                printf("Informe o id do produto: ");
                if (scanf("%i", &produto.id) != 1) {
                    printf("Entrada invalida!\n");
                    while (getchar() != '\n');
                    continue;
                }
                printf("Informe o nome do produto: ");
                getchar();
                fgets(produto.nome, sizeof(produto.nome), stdin);
                produto.nome[strcspn(produto.nome, "\n")] = '\0';
                printf("Informe o preco do produto: ");
                scanf("%f", &produto.preco);
                printf("Informe a quantidade do produto: ");
                scanf("%i", &produto.quantidade);
                inserirProduto(&raiz, produto);
                printf("Produto inserido com sucesso!\n");
                break;
            case 2:
                printf("Informe o id do produto que deseja BUSCAR: ");
                scanf("%i", &idBuscar);
                struct No *buscado = buscarProduto(raiz, idBuscar);
                if (buscado != NULL) {
                    printf("\nProduto encontrado!\n");
                    printf("Id: %i\n", buscado->produto.id);
                    printf("Nome: %s\n", buscado->produto.nome);
                    printf("Preco: %.2f\n", buscado->produto.preco);
                    printf("Quantidade: %i\n", buscado->produto.quantidade);
                } else {
                    printf("Produto nao encontrado...\n");
                }
                break;
            case 3:
                printf("Informe o id do produto que deseja REMOVER: ");
                scanf("%i", &idRemover);
                removerProduto(&raiz, idRemover);
                break;
            case 4:
                inOrder(raiz);
                break;
            case 5:
                printf("Digite o id do produto que deseje alterar: ");
                scanf("%i", &idAlterar);
                
                alterarProduto(&raiz, idAlterar);
                break;
            case 6:
                printf("Soma total dos precos e quantidade: \n");
                somaTotal(raiz, &soma);
                printf("Total: %.2f\n", soma);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    }
    liberarMemoriaArvore(raiz);
    printf("Encerrando o programa...\n");
    return 0;
}
