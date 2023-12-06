#include "interface.h"
#include "livros.h"
#include <locale.h>
#include "standart.h"

void mainMenu()
{
    limpa_tela();
    setlocale(LC_ALL, "");
    printf("\n============================================================================\n");
    printf("                               MENU PRINCIPAL                               \n");
    printf("----------------------------------------------------------------------------\n");
    printf("1. INCLUSÃO  2. LISTAGEM  3. ALTERAÇÃO 4. EXPORTAÇÃO 99. SAIR\n");
    printf("----------------------------------------------------------------------------\n");
    printf("Informe sua Opção: ");
}

void adicionaLivro()
{
    limpa_tela();
    printf("\n============================================================================\n");
    printf("                               ADICIONAR LIVRO                               \n");
    printf("-----------------------------------------------------------------------------\n");
    digitaLivro();
}

void listagem() {
    int quantidadeLivrosLidos = listaLivros();

    limpa_tela();

    printf("\n============================================================================\n");
    printf("                                LISTAGEM DE LIVROS                          \n");
    printf("----------------------------------------------------------------------------\n");

    if (quantidadeLivrosLidos == -1) {
        printf("Erro ao listar os livros.\n");
    } else if (quantidadeLivrosLidos == 0) {
        printf("Ops... Parece que não temos nenhum livro disponível no momento.\n");
    } else {
        for (int i = 0; i < quantidadeLivrosLidos; i++) {
            printf("Livro %d \n", i + 1);
            printf("ISBN: %s\n", arrayLivros[i].ISBN);
            printf("Título: %s", arrayLivros[i].titulo);
            printf(" - %s\n", arrayLivros[i].autor);
            printf("Editora: %s\n", arrayLivros[i].editora);
            printf("Número de Páginas: %d\n", arrayLivros[i].numPag);
            printf("Cidade: %s\n", arrayLivros[i].cidade);
            printf("Preço: %.2lfR$\n", arrayLivros[i].preco);
            printf("----------------------------------------------------------------------------\n");
        }
    }

    pausa_tela();
}


void edicaoLivro()
{
    listagem();
    limpa_tela();

    printf("\n============================================================================\n");
    printf("                                EDICAO DE LIVROS                          \n");
    printf("----------------------------------------------------------------------------\n");

    editaLivro();
}