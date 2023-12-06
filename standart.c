#include "standart.h"
#include <stdio.h>
#include <stdlib.h>

void limpa_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


void pausa_tela() {
    #ifdef _WIN32
        system("pause");
    #else
        printf("Pressione [Enter] para continuar...");
        while (getchar() != '\n')continue;
    #endif
}

void getString(char **string) 
{
    char c;
    int length = 0;
    *string = (char *)malloc(sizeof(char));
    (*string)[0] = '\0';
    if (*string == NULL) {
        exit(1);
    }
    while((c = getchar()) != '\n')
    {
        *string = (char *)realloc(*string, sizeof(char) * (length + 2));
        if (*string == NULL) {
            free(*string);
            exit(1);
        }
        (*string)[length] = c;
        (*string)[length + 1] = '\0';
        ++length;
    }
}
