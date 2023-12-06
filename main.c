#include "interface.h"
#include "livros.h"
#include "standart.h"

int main (int argc, char **argv)
{
    int option = -1;
    int end = 0;
    while(end == 0){
        if(end == 1)break;
        mainMenu();
        scanf("%d", &option);
        limpa_tela();

        switch (option)
        {
        case 1:
            adicionaLivro();
            break;
        
        case 2:
            listagem();
            break;

        case 3:
            edicaoLivro();
            break;

        case 4:
            exportaParaCSV();

        case 99:
            end = 1;
        
        default:
            break;
        }
        
        option = -1;
    }
    return 0;
}