#include "livros.h"
#include "standart.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

Livro arrayLivros[MAX_LIVROS];
int quantidadeLivros = 0;

void digitaLivro()
{
    Livro livro;

    printf("Digite o ISBN: ");
    scanf(" %13s", livro.ISBN);
    getchar();

    printf("Digite o título: ");
    getString(&livro.titulo);

    printf("Digite o autor(a): ");
    getString(&livro.autor);

    printf("Digite a editora: ");
    getString(&livro.editora);

    printf("Digite o idioma: ");
    scanf(" %3s", livro.idioma);
    getchar();

    printf("Digite o número de páginas do livro: ");
    scanf("%d", &livro.numPag);
    getchar();

    printf("Digite a cidade: ");
    getString(&livro.cidade);

    while(1){
        printf("Digite o preço: ");
        scanf("%lf", &livro.preco);
        if(livro.preco > 0)
            break;
        printf("valor inválido digitado\n\n");
    }

    salvaLivro(livro);
}

void salvaLivro(Livro livro) 
{
    FILE *arquivo = fopen("./livros.bin", "ab"); 
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    fwrite(livro.ISBN, sizeof(livro.ISBN), 1, arquivo);
    fwrite(livro.idioma, sizeof(livro.idioma), 1, arquivo);
    fwrite(&livro.numPag, sizeof(livro.numPag), 1, arquivo);
    fwrite(&livro.preco, sizeof(livro.preco), 1, arquivo);

    int length;
    
    length = strlen(livro.titulo);
    fwrite(&length, sizeof(length), 1, arquivo);
    fwrite(livro.titulo, sizeof(char), length, arquivo);

    length = strlen(livro.autor);
    fwrite(&length, sizeof(length), 1, arquivo);
    fwrite(livro.autor, sizeof(char), length, arquivo);

    length = strlen(livro.editora);
    fwrite(&length, sizeof(length), 1, arquivo);
    fwrite(livro.editora, sizeof(char), length, arquivo);

    length = strlen(livro.cidade);
    fwrite(&length, sizeof(length), 1, arquivo);
    fwrite(livro.cidade, sizeof(char), length, arquivo);

    fclose(arquivo);
}

int listaLivros() {
    FILE *arquivo = fopen("./livros.bin", "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    quantidadeLivros = 0;

     while (quantidadeLivros < MAX_LIVROS) {
        Livro livro;

        // Lê campos não-string
        if (fread(livro.ISBN, sizeof(livro.ISBN), 1, arquivo) != 1) break;
        if (fread(livro.idioma, sizeof(livro.idioma), 1, arquivo) != 1) break;
        if (fread(&livro.numPag, sizeof(livro.numPag), 1, arquivo) != 1) break;
        if (fread(&livro.preco, sizeof(livro.preco), 1, arquivo) != 1) break;

        // Lê campos string (título, autor, editora, cidade)
        int length;

        fread(&length, sizeof(length), 1, arquivo);
        livro.titulo = malloc(length + 1);
        fread(livro.titulo, sizeof(char), length, arquivo);
        livro.titulo[length] = '\0';

        fread(&length, sizeof(length), 1, arquivo);
        livro.autor = malloc(length + 1);
        fread(livro.autor, sizeof(char), length, arquivo);
        livro.autor[length] = '\0';

        fread(&length, sizeof(length), 1, arquivo);
        livro.editora = malloc(length + 1);
        fread(livro.editora, sizeof(char), length, arquivo);
        livro.editora[length] = '\0';

        fread(&length, sizeof(length), 1, arquivo);
        livro.cidade = malloc(length + 1);
        fread(livro.cidade, sizeof(char), length, arquivo);
        livro.cidade[length] = '\0';

        arrayLivros[quantidadeLivros] = livro;
        quantidadeLivros++;
    }

    fclose(arquivo);
    return quantidadeLivros;
}

void editaLivro() {
    char isbn[14];
    int encontrado = 0;

    printf("Digite o ISBN do livro que deseja editar: ");
    scanf(" %13s", isbn);

    Livro livro;

    for (int i = 0; i < quantidadeLivros; i++) {
        if (strcmp(isbn, arrayLivros[i].ISBN) == 0) {
            encontrado = 1;
            livro = arrayLivros[i];

            getchar();
            char *titulo;
            printf("Título atual: %s\n", livro.titulo);
            printf("Novo título (ou Enter para manter o antigo): ");
            getString(&titulo);
            if(titulo[0] != '\0')
                strcpy(livro.titulo, titulo);


            char *autor;
            printf("Autor atual: %s\n", livro.autor);
            printf("Novo autor (ou Enter para manter o antigo): ");
            getString(&autor);
            if(autor[0] != '\0')
                strcpy(livro.autor, autor);

            char *editora;
            printf("Editora atual: %s\n", livro.editora);
            printf("Nova editora (ou Enter para manter a antiga): ");
            getString(&editora);
            if(editora[0] != '\0')
                strcpy(livro.editora, editora);

            printf("Idioma atual: %s\n", livro.idioma);
            printf("Novo idioma: ");
            scanf(" %3s", livro.idioma);

            printf("Número de páginas atual: %d\n", livro.numPag);
            printf("Novo número de páginas: ");
            scanf("%d", &livro.numPag);
            getchar();

            char *cidade;
            printf("Cidade atual: %s\n", livro.cidade);
            printf("Nova cidade (ou Enter para manter a antiga): ");
            getString(&cidade);
            if(cidade[0] != '\0')
                strcpy(livro.cidade, cidade);

            printf("Preço atual: %.2lf\n", livro.preco);
            printf("Novo preço: ");
            scanf("%lf", &livro.preco);

            arrayLivros[i] = livro;

            break;
        }
    }

    if (encontrado) {
        FILE *arquivo = fopen("./livros.bin", "wb");
        if (arquivo == NULL) {
            perror("Erro ao abrir o arquivo");
            return;
        }

        for (int i = 0; i < quantidadeLivros; i++)
            salvaLivro(arrayLivros[i]);

        fclose(arquivo);

        if (!encontrado) {
            printf("Livro com ISBN %s não encontrado.\n", isbn);
        } else {
            printf("Livro editado com sucesso!\n");
        }
    }
}

void exportaParaCSV() {
    FILE *arquivoCSV = fopen("./exportacao.csv", "w");
    if (arquivoCSV == NULL) {
        perror("Erro ao abrir o arquivo CSV");
        return;
    }

    fprintf(arquivoCSV, "ISBN,Titulo,Autor,Editora,Idioma,NumPag,Cidade,Preco\n");

    int totalLivros = listaLivros(); 

    for (int i = 0; i < totalLivros; i++) {
        Livro livro = arrayLivros[i];
        fprintf(arquivoCSV, "%s,\"%s\",\"%s\",\"%s\",%s,%d,\"%s\",%.2lf\n",
            livro.ISBN, livro.titulo, livro.autor, livro.editora, 
            livro.idioma, livro.numPag, livro.cidade, livro.preco);
    }

    fclose(arquivoCSV);

    printf("Exportado com sucesso!");
    pausa_tela();
}
