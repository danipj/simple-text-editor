#include <stdio.h>
#include <stdlib.h>
#include "tela.h"
#include "listaDupla.h"
#define MALLOC(x) ((x *) malloc (sizeof(x)))

/***********************************************************************************************************************************/



/***********************************************************************************************************************************/


Lista* create(Lista *lista)
{
    //No *novo;
    //lista = MALLOC(Lista);
    lista = (Lista*)malloc(sizeof(Lista));
    lista->tamanho = 0;
    lista->inicio = lista->fim = NULL;
    return lista;


}

void writeC (Lista *lista, int ind, char c)
{
    No *novo;
    novo   = (No*)malloc(sizeof(No));
    novo->info = c;

    if (ind == 0)
    {
        novo->anterior = NULL;
        if (lista->tamanho == 0)
        {
            novo->proximo = NULL;
            lista->inicio = lista->fim = novo;
        }
        else
        {
            novo->proximo = lista->inicio;
            lista->inicio = novo;
        }
    }


    else if ((ind >= lista->tamanho))
    {
        novo->proximo = NULL;
        novo->anterior = lista->fim;
        lista->fim->proximo = novo;
        lista->fim = novo;
    }


    else
    {
        int i;
        No *percorre;
        percorre = lista->inicio;
        for (i = 0 ; i < ind-1 ; i++)
            percorre = percorre->proximo;
        No *aux;
        aux = percorre->proximo;
        percorre->proximo = novo;
        novo->anterior = percorre;
        novo->proximo = aux;
        aux->anterior = novo;
    }

    lista->tamanho++;
};

char readC  (Lista *lista, int ind)
{
    int i;
    No *percorre;
    percorre = lista->inicio;
    for (i = 0 ; i < ind ; i++)
        if (percorre->proximo != NULL)
            percorre = percorre->proximo;
        else break;
    return percorre->info;
};

char erase (Lista *lista, int ind)
{
    char retorno = 'N';
    if ((ind == 0) && (lista->tamanho == 1))
        free(lista->inicio);
    else if (ind == 0)
    {
        No *aux;
        aux = lista->inicio;
        retorno = lista->inicio->info;
        lista->inicio = lista->inicio->proximo;
        free(aux);
    }
    else if (ind >= lista->tamanho-1)
    {
        No *aux;
        aux = lista->fim;
        //printf("\n\n\n%c", lista->fim->anterior->info);
        if (lista->fim != NULL)
        {
            retorno = lista->fim->info;
            lista->fim = lista->fim->anterior;
        }
        free(aux);
    }
    else
    {
        int i;
        No *percorre;
        percorre = lista->inicio;
        for (i = 0 ; i < ind ; i++)
            percorre = percorre->proximo;
        retorno = percorre->info;

        No *ant, *prox;
        ant  = percorre->anterior;
        prox = percorre->proximo;
        ant->proximo = prox;
        prox->anterior = ant;
        free(percorre);
    }

    lista->tamanho--;
    return retorno;

};


int getTamanho(Lista *lista)
{
    return lista->tamanho;
};


