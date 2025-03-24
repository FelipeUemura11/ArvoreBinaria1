#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Livro {
    char titulo[35];
    char autor[45];
    float preco;
    int quant_disponivel;
};

struct No {
    struct Livro livro;
    struct No *dir;
    struct No *esq;
};

// Função para inserir um novo livro na arvore
void insert(struct No **raiz, struct Livro novoLivro){

    if (*raiz == NULL) {
        *raiz = (struct No *)malloc(sizeof(struct No));
        if (*raiz != NULL) {
            (*raiz)->livro = novoLivro;
            (*raiz)->esq = NULL;
            (*raiz)->dir = NULL;
        } else {
            printf("ERROR : insercao do [%s] invalida, memoria insuficiente.\n", novoLivro.titulo);
        }
    }else{
        if(strcmp(novoLivro.titulo, (*raiz)->livro.titulo) < 0) {
            insert(&((*raiz)->esq), novoLivro);
        }else if(strcmp(novoLivro.titulo, (*raiz)->livro.titulo) > 0) {
            insert(&((*raiz)->dir), novoLivro);
        }else{
            printf("Livro com este titulo ja existe na biblioteca...\n");
        }
    }
}

// Função de busca que retorna o noh encontrado
struct No *buscar(struct No *raiz, char buscaLivro[35]) {

    if (raiz == NULL){
        return NULL;
    }else{
        if(strcmp(buscaLivro, raiz->livro.titulo) == 0){
            return raiz;
        }else if(strcmp(buscaLivro, raiz->livro.titulo) < 0) {
            return buscar(raiz->esq, buscaLivro);
        }else{
            return buscar(raiz->dir, buscaLivro);
        }
    }
}

// Funcao para alterar o preço de um livro
void alterar(struct No *raiz, char tituloBusca[35], float precoNovo) {
    struct No *noEncontrado = buscar(raiz, tituloBusca);
    if(noEncontrado != NULL){
        noEncontrado->livro.preco = precoNovo;
        printf("\nPreco alterado com sucesso!\n");
        printf("Titulo: %s\n", noEncontrado->livro.titulo);
        printf("Autor: %s\n", noEncontrado->livro.autor);
        printf("Novo Preco: %.2f\n", noEncontrado->livro.preco);
        printf("Quantidade disponivel: %i\n", noEncontrado->livro.quant_disponivel);
    }else{
        printf("Livro nao encontrado...\n");
    }
}

// Listagem inOrder
void inOrder(struct No *raiz) {
    if(raiz != NULL){
        inOrder(raiz->esq);
        printf("\nTitulo: %s\n", raiz->livro.titulo);
        printf("Autor: %s\n", raiz->livro.autor);
        printf("Preço: %.2f\n", raiz->livro.preco);
        printf("Quantidade disponivel: %i\n", raiz->livro.quant_disponivel);
        inOrder(raiz->dir);
    }
}

// Liberar memoria da arvore recursivamente
void liberarArvore(struct No *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

int main(void) {
    struct No *raiz = NULL;
    struct Livro livro;
    int opcao = -1;
    float precoNovo = 0.0;
    char buscaLivro[35], tituloBusca[35];

    while (opcao != 0) {
        printf("\n======= BIBLIOTECA =======\n");
        printf("[1] Inserir livro\n");
        printf("[2] Buscar livro\n");
        printf("[3] Alterar preco do livro\n");
        printf("[4] Listar livros (inOrder)\n");
        printf("[0] Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                printf("Titulo do livro: ");
                fgets(livro.titulo, 35, stdin);
                livro.titulo[strcspn(livro.titulo, "\n")] = 0;

                printf("Autor do livro: ");
                fgets(livro.autor, 45, stdin);
                livro.autor[strcspn(livro.autor, "\n")] = 0;

                printf("Preco: ");
                scanf("%f", &livro.preco);

                printf("Quantidade disponivel: ");
                scanf("%d", &livro.quant_disponivel);
                getchar();

                insert(&raiz, livro);
                break;

            case 2:
                printf("Informe o titulo para busca: ");
                fgets(buscaLivro, 35, stdin);
                buscaLivro[strcspn(buscaLivro, "\n")] = 0;

                struct No *encontrado = buscar(raiz, buscaLivro);
                if (encontrado != NULL) {
                    printf("\nLivro encontrado!\n");
                    printf("Titulo: %s\n", encontrado->livro.titulo);
                    printf("Autor: %s\n", encontrado->livro.autor);
                    printf("Preco: %.2f\n", encontrado->livro.preco);
                    printf("Quantidade disponivel: %d\n", encontrado->livro.quant_disponivel);
                } else {
                    printf("Livro nao encontrado...\n");
                }
                break;

            case 3:
                printf("Titulo do livro para alterar o preco: ");
                fgets(tituloBusca, 35, stdin);
                tituloBusca[strcspn(tituloBusca, "\n")] = 0;

                printf("Novo preco: ");
                scanf("%f", &precoNovo);
                getchar();

                alterar(raiz, tituloBusca, precoNovo);
                break;

            case 4:
                printf("\n>>> List de livros (inOrder):\n");
                inOrder(raiz);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    }

    liberarArvore(raiz);
    return 0;
}
