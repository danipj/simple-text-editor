#include <stdio.h>
#include <stdlib.h>
#include "tela.h"
#include "linhas.h"
#define MALLOC(x) ((x *) malloc (sizeof(x)))

/***********************************************************************************************************************************/



/***********************************************************************************************************************************/


ListaDeLinhas* createLinhas(ListaDeLinhas *listaDeLinhas)
{
    //No *novo;
    //listaDeLinhas = MALLOC(ListaDeLinhas);
    listaDeLinhas = (ListaDeLinhas*)malloc(sizeof(ListaDeLinhas));
    listaDeLinhas->tamanho = 0;
    listaDeLinhas->inicio = NULL;
    listaDeLinhas->fim = NULL;

    return listaDeLinhas;
}

void writeLinhas (ListaDeLinhas *listaDeLinhas, int ind, Lista *c)
{
    Linha *novo;
    novo   = (Linha*)malloc(sizeof(Linha));
    novo->info = c;

    if (ind == 0 || listaDeLinhas->tamanho == 0)
    {
        novo->anterior = NULL;
        if (listaDeLinhas->tamanho == 0)
        {
            novo->proximo = NULL;
            listaDeLinhas->inicio = listaDeLinhas->fim = novo;
        }
        else
        {
            novo->proximo = listaDeLinhas->inicio;
            listaDeLinhas->inicio = novo;
        }
    }


    else if ((ind >= listaDeLinhas->tamanho))
    {
        novo->proximo = NULL;
        novo->anterior = listaDeLinhas->fim;
        listaDeLinhas->fim->proximo = novo;
        listaDeLinhas->fim = novo;
    }


    else
    {
        int i;
        Linha *percorre;
        percorre = listaDeLinhas->inicio;
        for (i = 0 ; i < ind-1 ; i++)
            percorre = percorre->proximo;
        Linha *aux;
        aux = percorre->proximo;
        percorre->proximo = novo;
        novo->anterior = percorre;
        novo->proximo = aux;
        aux->anterior = novo;
    }

    listaDeLinhas->tamanho++;
};

Lista* readLinhas  (ListaDeLinhas *listaDeLinhas, int ind)
{
    int i;
    Linha *percorre;
    percorre = listaDeLinhas->inicio;
    for (i = 0 ; i < ind ; i++)
        percorre = percorre->proximo;
    return percorre->info;
};

Lista* eraseLinhas (ListaDeLinhas *listaDeLinhas, int ind)
{
    Lista* retorno;
    if ((ind == 0) && (listaDeLinhas->tamanho == 1))
        free(listaDeLinhas->inicio);
    else if (ind == 0)
    {
        Linha *aux;
        aux = listaDeLinhas->inicio;
        retorno = listaDeLinhas->inicio->info;
        listaDeLinhas->inicio = listaDeLinhas->inicio->proximo;
        free(aux);
    }
    else if (ind >= listaDeLinhas->tamanho-1)
    {
        Linha *aux;
        aux = listaDeLinhas->fim;
        retorno = listaDeLinhas->fim;
        listaDeLinhas->fim = listaDeLinhas->fim->anterior;
        free(aux);
    }
    else
    {
        int i;
        Linha *percorre;
        percorre = listaDeLinhas->inicio;
        for (i = 0 ; i < ind ; i++)
            percorre = percorre->proximo;
        retorno = percorre->info;

        Linha *ant, *prox;
        ant  = percorre->anterior;
        prox = percorre->proximo;
        ant->proximo = prox;
        prox->anterior = ant;
        free(percorre);
    }

    listaDeLinhas->tamanho--;
    return retorno;

};

void verificarLinhas(ListaDeLinhas *listaDeLinhas)
{
    Linha *percorre;
    percorre = listaDeLinhas->inicio;


    while (percorre != NULL)
    {
        //printf("\n\n\n\n ant:%p   atual:%p    pro:%p" , percorre->anterior , percorre , percorre->proximo);
        if (percorre->info->tamanho == 101)
        {
            if (percorre == listaDeLinhas->fim)
            {
                Lista *novaLinha;
                novaLinha = create(novaLinha);
                writeLinhas(listaDeLinhas, listaDeLinhas->tamanho+1 , novaLinha);
                //printf("\n\n\n\n\n\n\n\n\n ! %p" , listaDeLinhas->fim->info);
                char letra = erase( listaDeLinhas->fim->anterior->info , listaDeLinhas->fim->anterior->info->tamanho);
                writeC(
                      listaDeLinhas->fim->info,
                      0 ,
                      letra);
                //printf("\n\n\n\n\n\n\n\n\n criou nova Linha :%p !" , listaDeLinhas->fim);
                //printf("\n! %c" , letra);


            }
            else
            {
                //printf("\n\n\n\n\n\n\n Linha :%p !" , listaDeLinhas->fim);
                //printf("\n\n\n\n\n\n\n Linha :%c !" , listaDeLinhas->fim->anterior->anterior->info->fim->info);
                if (percorre->info != NULL)
                    writeC(
                          percorre->proximo->info ,
                          0 ,
                          erase(percorre->info , percorre->info->tamanho));



            }

        }
        percorre = percorre->proximo;
    }
}



int getTamanhoL(ListaDeLinhas *listaDeLinhas)
{
    return listaDeLinhas->tamanho;
};

