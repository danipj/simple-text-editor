#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include "listaDupla.h"
#include "linhas.h"
#include "tela.h"

int main()
{
/*********************************************************************************************************************************************************/
    //escrevendo a tela incial
    unsigned int traco;

    unsigned int cod1, cod2;
             int *x    , *y,
                 *xTelaInicio, *xTelaFim,
                 *yTelaInicio, *yTelaFim,
                 *xImaginario, *yImaginario;

    x           = (int*)malloc(sizeof(int));
    y           = (int*)malloc(sizeof(int));
    xTelaInicio = (int*)malloc(sizeof(int));
    xTelaFim    = (int*)malloc(sizeof(int));
    yTelaInicio = (int*)malloc(sizeof(int));
    yTelaFim    = (int*)malloc(sizeof(int));
    xImaginario = (int*)malloc(sizeof(int));
    yImaginario = (int*)malloc(sizeof(int));


    *x           = 0;
    *y           = 0;

    *xTelaInicio = 0;
    *xTelaFim    = 79;

    *yTelaInicio = 3;
    *yTelaFim    = 3;

    *xImaginario  = 0;
    *yImaginario  = 0;


    vaParaCL (*xImaginario,*yImaginario);

    ajustaCorDoFundo(CINZA_ESCURO);
    limpaTela();
    ajustaCorDoTexto(PRETO);

    vaParaCL (32,0);
    printf("Editor de Texto");
    vaParaCL (16,1);
    printf("By Raphael Issamu 11185 & Guilherme Murari 11167");
    vaParaCL (0,2);
    for (traco=0; traco<=79; traco++)
		escreva ("%c", 205);
    *xImaginario = 0;
    *yImaginario = 3;
	vaParaCL (0,3);

/*********************************************************************************************************************************************************/

    //criando as listas
    Lista* linhaInicial;
    ListaDeLinhas* listaDeLinhas;

    linhaInicial  = create(linhaInicial);
    //printf("tamanho da linha : %d\n",linhaInicial->tamanho);
    listaDeLinhas = createLinhas(listaDeLinhas);
    //printf("tamanho das linhas : %d\n",listaDeLinhas->tamanho);


    writeLinhas(listaDeLinhas, listaDeLinhas->tamanho , linhaInicial);
   // printf("tamanho das linhas : %d\n",listaDeLinhas->tamanho);
    listaDeLinhas->atual = listaDeLinhas->inicio;
    //printf("tamanho da linha : %d\n",listaDeLinhas->atual->info->tamanho);




/*********************************************************************************************************************************************************/

    //while principal que le o que o usuario digitou para realizar
	//a operacao desejada
    do
    {
        if (kbhit())
		{
			cod1 = getch ();
            if (kbhit())
			{
                cod2 = getch ();
                    if (cod1==Tecla)
                    {
					 switch (cod2)
                    {
                        case Esq:   setaEsquerda(listaDeLinhas,
                                            x          ,   y      ,
                                            xTelaInicio,  xTelaFim,
                                            yTelaInicio,  yTelaFim,
                                            xImaginario,  yImaginario);
                                    //vaParaCL (*x,*y);
                                    break;

                        case Dir:   setaDireita(listaDeLinhas,
                                            x          ,   y      ,
                                            xTelaInicio,  xTelaFim,
                                            yTelaInicio,  yTelaFim,
                                            xImaginario,  yImaginario);
                                    //vaParaCL (*x,*y);
                                    break;

                        case Cima:  setaCima(listaDeLinhas,
                                            x          ,   y      ,
                                            xTelaInicio,  xTelaFim,
                                            yTelaInicio,  yTelaFim,
                                            xImaginario,  yImaginario);
                                    //vaParaCL (*x,*y);
                                    break;

                        case Baixo: setaBaixo(listaDeLinhas,
                                            x          ,   y      ,
                                            xTelaInicio,  xTelaFim,
                                            yTelaInicio,  yTelaFim,
                                            xImaginario,  yImaginario);
                                    //vaParaCL (*x,*y);
                                    break;

						case PageUp  : break;
						case PageDown: break;
                    }
					//fflush (stdout);
                    }
			}



			else if (cod1 == BackSpace)
            {
                backSpace(listaDeLinhas,
                          x          ,   y      ,
                          xTelaInicio,  xTelaFim,
                          yTelaInicio,  yTelaFim,
                          xImaginario,  yImaginario);
                //vaParaCL (*x,*y);
                /*
                --(*x);
                verificarXY(listaDeLinhas,x,y);
                vaParaCL (*x,*y);
                escreva ("%c", 32);
                verificarXY(listaDeLinhas,x,y);
                */


             }

            else if (cod1 == Enter)
            {
                /*
                ++(*y);
                (*x) = 0;
                vaParaCL(*x,*y);
                */
            }

			else
			{

               armazenarCaracter(listaDeLinhas,
                                 x          , y       ,
                                 xTelaInicio, xTelaFim,
                                 yTelaInicio, yTelaFim,
                                 xImaginario, yImaginario,
                                 cod1);

               // printf("\n%p" , listaDeLinhas->atual);

               /*
               writeC(listaDeLinhas->atual->info , *x , cod1);//armazena na lista atual o caracter escrito

               verificarEscrita(listaDeLinhas,
                                 x          ,   y      ,
                                 xTelaInicio,  xTelaFim,
                                 yTelaInicio,  yTelaFim,
                                 xImaginario,  yImaginario); // verifica as coordenadas X e YatualizarTela(listaDeLinhas,

                vaParaCL (*xImaginario,*yImaginario);

                if (*x > 79)
                    vaParaCL (79,*y);
                else
                    vaParaCL (*x,*y);
                */


            }
                fflush (stdout);
            }
        }

    while (cod1!=27);

    free(listaDeLinhas);
    return 0;
}
