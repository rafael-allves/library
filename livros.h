#ifndef LIVROS_H
#define LIVROS_H

#define MAX_LIVROS 100

typedef struct {
    char ISBN[14];
    char *titulo;
    char *autor;
    char *editora;
    char idioma[4];
    int numPag;
    char *cidade;
    double preco;
}Livro;

extern Livro arrayLivros[MAX_LIVROS];
extern int quantidadeLivros;

/**
 * @brief função pra criação de livros
*/
void digitaLivro();

/**
 * @brief salva o livro em um arquivo binário
 * @param livro livro a ser salvo
*/
void salvaLivro(Livro livro);

/**
 * @brief lista os livros criados dentro do arquivo livros.bin
 * @param arrayLivros array de livros 
 * @param quantidade a referência da quantidade de livros
 * @note quantidade é passada por referência para que todo app tenha noção da quantidade
 * @return A quantidade de livros lidos ou algum codigo de erro
*/
int listaLivros();

/**
 * @brief passada um codigo ISBN edita o livro que está nela!
*/
void editaLivro();

/**
 * @brief Exporta arquivos binário pra CSV
*/
void exportaParaCSV();

#endif