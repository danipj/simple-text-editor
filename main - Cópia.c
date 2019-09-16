#include <stdio.h>
#include <stdlib.h>
#include "listaDupla.h"
#include "tela.h"

int main()
{
    limpaTela();
    printf("Hello world!\n");
    Lista *linha;
    linha = create(linha);

    /*
    linha = (Lista*)malloc(sizeof(Lista));
    linha->tamanho = 0;
    linha->inicio = linha->fim = NULL;


    printf("tamanho da lista : %i\n" , linha->tamanho);
    printf("inicio : %p , fim : %p\n" , linha->inicio , linha->fim);
    */

    write(linha, 0, 'A');
    write(linha, 1, 'B');
    write(linha, 1, 'C');
    write(linha, 3, 'D');

    int i;
    printf("[");
    for (i = 0 ; i < linha->tamanho ; i++)
    {
        printf(" %c " , read(linha, i));
    }
    printf("]\n");

    printf("Elemento apagado : %c\n" , erase(linha, 3));

    printf("[");
    for (i = 0 ; i < linha->tamanho ; i++)
    {
        printf(" %c " , read(linha, i));
    }
    printf("]\n");

    free(linha);


    return 0;
}
