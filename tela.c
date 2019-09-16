#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include "tela.h"
#include <string.h>
#include <unistd.h>

unsigned int minC ()
{
    return 0;
}

unsigned int minL ()
{
    return 0;
}

unsigned int maxC ()
{
    HANDLE idJanela = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO infoJanela;
    GetConsoleScreenBufferInfo (idJanela, &infoJanela);

    return (unsigned int)infoJanela.srWindow.Right;
}

unsigned int maxL ()
{
    HANDLE idJanela = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO infoJanela;
    GetConsoleScreenBufferInfo (idJanela, &infoJanela);

    return (unsigned int)infoJanela.srWindow.Bottom;
}

unsigned int cAtual ()
{
    HANDLE idJanela = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO InfTela;

    GetConsoleScreenBufferInfo(idJanela, &InfTela);

    return (unsigned int)InfTela.dwCursorPosition.X;
}

unsigned int lAtual ()
{
    HANDLE idJanela = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO InfTela;

    GetConsoleScreenBufferInfo(idJanela, &InfTela);

    return (unsigned int)InfTela.dwCursorPosition.Y;
}

void vaParaCL (unsigned int col, unsigned int lin)
{
    HANDLE idJanela = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO infoJanela;
    GetConsoleScreenBufferInfo (GetStdHandle(STD_OUTPUT_HANDLE), &infoJanela);

    if (col>=minC() && col<=maxC() && lin>=minL() && lin<=maxL())
    {
       COORD coordenada = {col,lin};
       SetConsoleCursorPosition(idJanela, coordenada);
    }
}

Cor corDoTexto ()
{
    HANDLE idJanela = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO corDeFrenteTela;
    GetConsoleScreenBufferInfo (idJanela, &corDeFrenteTela);

    return (Cor)(corDeFrenteTela.wAttributes & 0x0F);
}

void ajustaCorDoTexto (Cor cor)
{
    HANDLE idJanela = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(idJanela, (corDoFundo () << 4) | cor);
}

Cor corDoFundo ()
{
    HANDLE idJanela = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO corDeFrenteTela;
    GetConsoleScreenBufferInfo (idJanela, &corDeFrenteTela);

    return (Cor)(corDeFrenteTela.wAttributes >> 4);
}

void ajustaCorDoFundo(Cor cor)
{
    HANDLE idJanela = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute( idJanela, (cor << 4) | corDoTexto ());
}

void limpaAteFimDaL ()
{
	CONSOLE_SCREEN_BUFFER_INFO infoJanela;
	HANDLE idJanela = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordenada;
	DWORD qtdCelsAfetadas;
	int largura;

	coordenada.X = cAtual();
	coordenada.Y = lAtual();

	GetConsoleScreenBufferInfo(idJanela, &infoJanela);

	largura = maxC() - cAtual() + 1;

	FillConsoleOutputCharacter(idJanela, ' ', largura, coordenada, &qtdCelsAfetadas);
	FillConsoleOutputAttribute(idJanela, infoJanela.wAttributes, largura, coordenada, &qtdCelsAfetadas);
}

void limpaTela ()
{
	CONSOLE_SCREEN_BUFFER_INFO infoJanela;
	HANDLE idJanela = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordenada;
	DWORD qtdCelsAfetadas;
	int largura, altura;

	coordenada.X = 0;
	coordenada.Y = 0;

	GetConsoleScreenBufferInfo(idJanela, &infoJanela);

	largura = infoJanela.dwMaximumWindowSize.X;
	altura  = infoJanela.dwMaximumWindowSize.Y;

	FillConsoleOutputCharacter(idJanela, ' ', largura * altura, coordenada, &qtdCelsAfetadas);
	FillConsoleOutputAttribute(idJanela, infoJanela.wAttributes, largura * altura, coordenada, &qtdCelsAfetadas);

	vaParaCL (0,0);
}

void apagaL ()
{
    HANDLE idJanela = GetStdHandle(STD_OUTPUT_HANDLE);
    PCHAR_INFO bloco;
    COORD tamanho,
    coordenada = {0,0};
    SMALL_RECT quadrado;

    CONSOLE_SCREEN_BUFFER_INFO infoJanela;
    GetConsoleScreenBufferInfo (GetStdHandle(STD_OUTPUT_HANDLE), &infoJanela);

    tamanho.X = maxC ();
    tamanho.Y = maxL () - lAtual() + 1;
    quadrado.Left = 0;
    quadrado.Right = tamanho.X - 1;
    quadrado.Top = lAtual() + 1;
    quadrado.Bottom = quadrado.Top + tamanho.Y + 1;

    bloco = (CHAR_INFO*) malloc (tamanho.X * tamanho.Y);

    ReadConsoleOutput(idJanela, bloco, tamanho, coordenada, &quadrado);

    quadrado.Bottom--;
    quadrado.Top--;

    WriteConsoleOutput(idJanela, bloco, tamanho, coordenada, &quadrado);

    vaParaCL(0,infoJanela.srWindow.Bottom - 1);
    limpaAteFimDaL();

    vaParaCL(0,lAtual());
}

void insereL ()
{
    HANDLE idJanela = GetStdHandle(STD_OUTPUT_HANDLE);
    PCHAR_INFO bloco;
    COORD tamanho,
    coordenada = {0,0};
    SMALL_RECT quadrado;

    CONSOLE_SCREEN_BUFFER_INFO infoJanela;
    GetConsoleScreenBufferInfo (GetStdHandle(STD_OUTPUT_HANDLE), &infoJanela);

    tamanho.X = maxC ();
    tamanho.Y = maxL () - lAtual() + 1;

    quadrado.Left = 0;
    quadrado.Right = tamanho.X - 1;
    quadrado.Top = lAtual();
    quadrado.Bottom = quadrado.Top + tamanho.Y;

    bloco = (CHAR_INFO*) malloc (tamanho.X * tamanho.Y);

    ReadConsoleOutput(idJanela, bloco, tamanho, coordenada, &quadrado);

    quadrado.Bottom++;
    quadrado.Top++;

    vaParaCL(0,lAtual());
    limpaAteFimDaL();

    WriteConsoleOutput(idJanela, bloco, tamanho, coordenada, &quadrado);
}

void someCursor ()
{
    HANDLE idJanela = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO infCursor;

    GetConsoleCursorInfo(idJanela, &infCursor);
    infCursor.bVisible = FALSE;
    SetConsoleCursorInfo(idJanela, &infCursor);
}

void voltaCursor ()
{
    HANDLE idJanela = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO infCursor;

    GetConsoleCursorInfo(idJanela, &infCursor);
    infCursor.bVisible = TRUE;
    SetConsoleCursorInfo(idJanela, &infCursor);
}

void escreva (char* fmt,...)
{
    unsigned int comprimento, cabe;
    char str[2001];
    va_list  args;

    HANDLE idJanela = GetStdHandle(STD_OUTPUT_HANDLE);
    PCHAR_INFO bloco;
    COORD tamanho,
    coordenada = {0,0};
    SMALL_RECT quadrado;

    CONSOLE_SCREEN_BUFFER_INFO infoTela;

    char ultimo;
    unsigned int temUltimo = 0;

    va_start(args,fmt);
    vsprintf(str, fmt,args);

    comprimento = strlen(str);
    cabe = 2000 - lAtual()*(maxC()+1) - cAtual();

    if (comprimento>cabe)
    {
        str[cabe] = '\0';
        comprimento = cabe;
    }

    if (comprimento - (maxC()-cAtual()+1) - (maxL()-lAtual())*(maxC()+1) == 0)
    {
        ultimo    = str [comprimento-1];
        temUltimo = 1;
        str[comprimento-1] = '\0';
    }

    printf (str);

    if (temUltimo)
    {
        GetConsoleScreenBufferInfo (idJanela, &infoTela);

        tamanho.X = 1;
        tamanho.Y = 1;

        quadrado.Left = cAtual();
        quadrado.Right = quadrado.Left;
        quadrado.Top = lAtual();
        quadrado.Bottom = quadrado.Top;

        bloco = (CHAR_INFO*) malloc (tamanho.X * tamanho.Y);

        bloco[0].Attributes = (corDoFundo()<<4) | corDoTexto();
        bloco[0].Char.AsciiChar = ultimo;

        WriteConsoleOutput(idJanela, bloco, tamanho, coordenada, &quadrado);
    }


}




void setaDireita(ListaDeLinhas* listaDeLinhas,
                  int *x          , int *y,
                  int *xTelaInicio, int *xTelaFim,
                  int *yTelaInicio, int *yTelaFim,
                  int *xImaginario, int *yImaginario)
{
    if (*x < listaDeLinhas->atual->info->tamanho)
    {
        ++(*x);

        if (*xImaginario < listaDeLinhas->atual->info->tamanho &&
            *xImaginario < 79)
            ++(*xImaginario);

        if (*xImaginario == 0 &&
            listaDeLinhas->atual->info->tamanho == 0 &&
            listaDeLinhas->tamanho == 1)
            --(*x);


        if (*x >= listaDeLinhas->atual->info->tamanho)
        {

            if (listaDeLinhas->atual != NULL &&
                listaDeLinhas->atual->proximo != NULL)
            {

                atualizarTela(listaDeLinhas,
                              *x            ,  *y       ,
                               0            ,  79       ,
                              *yTelaInicio  ,  *yTelaFim,
                              *xImaginario  ,  *yImaginario);

                *xTelaInicio = *x = 0;
                *xTelaFim = 79;
                *xImaginario = 0;
                ++(*y);
                ++(*yImaginario);
                listaDeLinhas->atual = listaDeLinhas->atual->proximo;


                atualizarTela(listaDeLinhas,
                              *x            ,  *y      ,
                              *xTelaInicio,   *xTelaFim,
                              *yTelaInicio  ,  *yTelaFim,
                              *xImaginario  ,  *yImaginario);


            }
        }

        else if (*x > 79 && *xImaginario == 79 && *xTelaInicio < 20)
        {
            ++(*xTelaInicio);
            ++(*xTelaFim);

        atualizarTela(listaDeLinhas,
                      *x          ,  *y      ,
                      *xTelaInicio,  *xTelaFim,
                      *yTelaInicio,  *yTelaFim,
                      *xImaginario,  *yImaginario);

        }
    }

    //printf("\n\n\n\npos x : %.3d xtela : %.3d   xImaginario  :  %.3d" , *x , *xTelaInicio , *xImaginario);
    //printf("\n\n\n\n ant:%p   atual:%p    pro:%p" , listaDeLinhas->atual->anterior , listaDeLinhas->atual , listaDeLinhas->atual->proximo);
    printf("\n\n\n\n tam:%.3d/%.3d",listaDeLinhas->tamanho,listaDeLinhas->atual->info->tamanho);

    vaParaCL (*xImaginario,*yImaginario);

}



void setaEsquerda(ListaDeLinhas* listaDeLinhas,
                  int *x          , int *y,
                  int *xTelaInicio, int *xTelaFim,
                  int *yTelaInicio, int *yTelaFim,
                  int *xImaginario, int *yImaginario)
{
    --(*x);
    if (*xImaginario > 0)
        --(*xImaginario);

    if (*x == -1)
    {
        if (listaDeLinhas->atual->anterior != NULL)
        {
            if (*yImaginario > 3)
            {
                --(*y);
                --(*yImaginario);
                /*
                Verificar ytela depois
                */
                listaDeLinhas->atual = listaDeLinhas->atual->anterior;

                *x = listaDeLinhas->atual->info->tamanho;
                if (*x = 100)
                    *x = 99;

                if (*x > 79)
                {
                     if (*x == 100)
                     {
                         *xTelaInicio = 20;
                         *xTelaFim    = 100;
                         *xImaginario = 79;
                     }

                    else
                    {
                        *xTelaInicio = *x - 79;
                        *xTelaFim    = *x;
                        *xImaginario = 79;
                    }

                        atualizarTela(listaDeLinhas,
                                      *x          ,  *y      ,
                                      *xTelaInicio,  *xTelaFim,
                                      *yTelaInicio,  *yTelaFim,
                                      *xImaginario,  *yImaginario);
                }
                else
                {
                    *xTelaInicio = 0;
                    *xTelaFim = 79;
                    *xImaginario = *x;
                    atualizarTela(listaDeLinhas,
                                  *x          ,  *y      ,
                                  *xTelaInicio,  *xTelaFim,
                                  *yTelaInicio,  *yTelaFim,
                                  *xImaginario,  *yImaginario);
                }
                //
            }
        }
        else
        {
            *x           = 0;
            *xImaginario = 0;
            *xTelaInicio = 0;
            *xTelaFim    = 79;
        }
    }

    else if (*x < *xTelaInicio)
    {
        --(*xTelaInicio);
        --(*xTelaFim);
        *xImaginario = 0;
        atualizarTela(listaDeLinhas,
                      *x          ,  *y      ,
                      *xTelaInicio,  *xTelaFim,
                      *yTelaInicio,  *yTelaFim,
                      *xImaginario,  *yImaginario);

    }

    //printf("\n\n\n\npos x : %.3d xtela : %.3d" , *x , *xTelaInicio);
    //printf("\n\n\n\n ant:%p   atual:%p    pro:%p" , listaDeLinhas->atual->anterior , listaDeLinhas->atual , listaDeLinhas->atual->proximo);
    printf("\n\n\n\n tam:%.3d/%.3d",listaDeLinhas->tamanho,listaDeLinhas->atual->info->tamanho);
    vaParaCL (*xImaginario,*yImaginario);



}






void setaCima(ListaDeLinhas* listaDeLinhas,
              int *x          , int *y,
              int *xTelaInicio, int *xTelaFim,
              int *yTelaInicio, int *yTelaFim,
              int *xImaginario, int *yImaginario)
{
    if (*yImaginario > 3)
    {
        --(*y);
        --(*yImaginario);
        listaDeLinhas->atual = listaDeLinhas->atual->anterior;
        if (listaDeLinhas->atual->info->tamanho < *x)
        {
            *xImaginario = listaDeLinhas->atual->info->tamanho;
            *x = *xImaginario;
        }
    }
    vaParaCL (*xImaginario,*yImaginario);
}





void setaBaixo(ListaDeLinhas* listaDeLinhas,
               int *x          , int *y,
               int *xTelaInicio, int *xTelaFim,
               int *yTelaInicio, int *yTelaFim,
               int *xImaginario, int *yImaginario)
{

    if (*yImaginario < listaDeLinhas->tamanho)
    {
        ++(*y);
        ++(*yImaginario);
        listaDeLinhas->atual = listaDeLinhas->atual->proximo;
        if (listaDeLinhas->atual->info->tamanho < *x)
        {
            *xImaginario = listaDeLinhas->atual->info->tamanho;
            *x = *xImaginario;
        }
    }
    vaParaCL (*xImaginario,*yImaginario);

}

void verificarEscrita(ListaDeLinhas* listaDeLinhas,
                      int *x          , int *y,
                      int *xTelaInicio, int *xTelaFim,
                      int *yTelaInicio, int *yTelaFim,
                      int *xImaginario, int *yImaginario)
{
    ++(*x);

    verificarLinhas(listaDeLinhas);

    if (*xImaginario < 79)
        ++(*xImaginario);
    if (*x > 79 && *xTelaInicio < 20)
    {
        ++(*xTelaInicio);
        ++(*xTelaFim);
    }
    if (*x == 101)
    {
            *x = 1;
            *xTelaInicio = 0;
            *xTelaFim = 79;
            *xImaginario = 1;
            ++(*y);
            ++(*yImaginario);

            if (listaDeLinhas->atual->proximo != NULL)
                listaDeLinhas->atual = listaDeLinhas->atual->proximo;


    }

    atualizarTela(listaDeLinhas,
                  *x          ,  *y      ,
                  *xTelaInicio,  *xTelaFim,
                  *yTelaInicio,  *yTelaFim,
                  *xImaginario,  *yImaginario);

    printf("\n\n\n\n tam:%.3d/%.3d",listaDeLinhas->tamanho,listaDeLinhas->atual->info->tamanho);



    //printf("\n\n\n\npos x : %.3d xtela : %.3d   xImaginario  :  %.3d" , *x , *xTelaInicio , *xImaginario);

    vaParaCL (*xImaginario,*yImaginario);


}






void backSpace(ListaDeLinhas* listaDeLinhas,
               int *x          , int *y,
               int *xTelaInicio, int *xTelaFim,
               int *yTelaInicio, int *yTelaFim,
               int *xImaginario, int *yImaginario)
{
    if ((listaDeLinhas->inicio != listaDeLinhas->atual) ||
        (listaDeLinhas->inicio == listaDeLinhas->atual && listaDeLinhas->atual->info->tamanho > 0))
    {
        if (*x == 0){
            listaDeLinhas->atual = listaDeLinhas->atual->anterior;
            --(*y);
            --(*yImaginario);

            *x = listaDeLinhas->atual->info->tamanho;

            if (*x > 79)
            {
                if (*x == 100)
                {
                    *x = 99;
                    *xTelaInicio = 20;
                    *xTelaFim     = 100;
                    *xImaginario = 79;
                }

                else
                {
                    *xTelaInicio = *x - 79;
                    *xTelaFim    = *x;
                    *xImaginario = 79;
                }

            }
            else
            {
                *xTelaInicio = 0;
                *xTelaFim = 79;
                *xImaginario = *x;
            }



            atualizarTela(listaDeLinhas,
                          *x          ,  *y      ,
                          *xTelaInicio,  *xTelaFim,
                          *yTelaInicio,  *yTelaFim,
                          *xImaginario,  *yImaginario);

        }

        else
        {
            erase(listaDeLinhas->atual->info , *x-1);

            atualizarTela(listaDeLinhas,
                          *x          ,  *y      ,
                          *xTelaInicio,  *xTelaFim,
                          *yTelaInicio,  *yTelaFim,
                          *xImaginario,  *yImaginario);

            setaEsquerda(listaDeLinhas,
                         x          ,   y      ,
                         xTelaInicio,  xTelaFim,
                         yTelaInicio,  yTelaFim,
                         xImaginario,  yImaginario);



            //vaParaCL (*xImaginario,*yImaginario);
        }


    }

}





void atualizarTela(ListaDeLinhas* listaDeLinhas,
                   int x          , int y,
                   int xTelaInicio, int xTelaFim,
                   int yTelaInicio, int yTelaFim,
                   int xImaginario, int yImaginario)
{
    someCursor();


    int i;
    //for (i = *xTelaInicio ; i < listaDeLinhas->atual->info->tamanho ; i++)//sevcrever a linha atual desde o comeco
    Linha *percorre;
    percorre = listaDeLinhas->inicio;
    int c = 3;

    while (percorre != NULL)
    {
        int count = 0;
        char *line;
        line = (char*)malloc(listaDeLinhas->tamanho*100*sizeof(char));
        for (i = xTelaInicio ; i < percorre->info->tamanho ; i++)//sevcrever a linha atual desde o comeco
        {
            *(line+(count)) = readC(percorre->info, i);
            ++count;
            if (count == 80)
            {
                break;
            }
        }
        *(line+(count)) = '\0';
        vaParaCL(0,c++);
        limpaAteFimDaL();
        escreva ("%s", line);
        free(line);
        percorre = percorre->proximo;
    }

    voltaCursor();



}

void armazenarCaracter(ListaDeLinhas* listaDeLinhas,
                       int *x          , int *y,
                       int *xTelaInicio, int *xTelaFim,
                       int *yTelaInicio, int *yTelaFim,
                       int *xImaginario, int *yImaginario,
                       char caracter)
{
    //1.)Verificar se jah existem linhas
    if (listaDeLinhas->tamanho == 0)
    {
        //criar uma linha
        //escrever o primeiro caracter nela
        Lista* linhaInicial;
        linhaInicial  = create(linhaInicial);
        writeLinhas(listaDeLinhas, 0 , linhaInicial);
        listaDeLinhas->atual = listaDeLinhas->inicio;
    }
    else
    {
        //2.)Verificar se a linha atual esta no limite do tamaho
        if (listaDeLinhas->atual->info->tamanho == 100)
        {
            //chegar na ultima linha

            //se essa linha tambem estiver cheia, criar uma nova linha vazia
            if (listaDeLinhas->fim->info->tamanho == 100)
            {
                //criar uma nova linha
                Lista* novaLinha;
                novaLinha  = create(novaLinha);
                writeLinhas(listaDeLinhas, listaDeLinhas->tamanho , novaLinha);
            }

            Linha *ponteiro;
            ponteiro = listaDeLinhas->fim;

            //fazer ateh que chegue na primeira linha
            while (ponteiro != listaDeLinhas->inicio)
            {
                //pegar a ultima letra da linha anterior escrever nessa linha
                writeC(
                    ponteiro->info,
                    0,
                    erase(ponteiro->anterior->info, ponteiro->info->tamanho));
                ponteiro = ponteiro->anterior;
            }

            //escrever o caracter
            writeC(listaDeLinhas->atual->info , *x , caracter);
        }
        //caso nao, inserir na linha normalmente
        else
        {
            //escrever caracter normalmente
            writeC(listaDeLinhas->atual->info , *x , caracter);
        }
    }


    ++(*x);

    if (*xImaginario < 79)
        ++(*xImaginario);
    if (*x > 79 && *xTelaInicio < 20)
    {
        ++(*xTelaInicio);
        ++(*xTelaFim);
    }
    if (*x == 101)
    {
            *x = 1;
            *xTelaInicio = 0;
            *xTelaFim = 79;
            *xImaginario = 1;
            ++(*y);
            ++(*yImaginario);

            if (listaDeLinhas->atual->proximo != NULL)
                listaDeLinhas->atual = listaDeLinhas->atual->proximo;


    }

    atualizarTela(listaDeLinhas,
                  *x          ,  *y      ,
                  *xTelaInicio,  *xTelaFim,
                  *yTelaInicio,  *yTelaFim,
                  *xImaginario,  *yImaginario);

    printf("\n\n\n\n tam:%.3d/%.3d",listaDeLinhas->tamanho,listaDeLinhas->atual->info->tamanho);

    //printf("\n\n\n\npos x : %.3d xtela : %.3d   xImaginario  :  %.3d" , *x , *xTelaInicio , *xImaginario);

    vaParaCL (*xImaginario,*yImaginario);


    //2.)Verificar se a linha atual esta no limite do tamaho
        //Caso esteja, empurrar os demais caracteres
          //Chegar na ultima linha
            //Se ela tambem estiver cheia, criar uma nova linha
              //Escrever no comeco dessa linha e apagar o ultimo caracter da linha anterior

}


void apagarTexto()
{
	int i;
	for (i = 3 ; i < 80 ; i++)
	{
	    vaParaCL (0,i);
	    limpaAteFimDaL();
	}

	vaParaCL (0,3);

}







