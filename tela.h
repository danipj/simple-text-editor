#include "linhas.h"
#include "listaDupla.h"


#ifndef TELA
#define TELA


typedef
    enum Cor
    {
        PRETO          =  0,
        AZUL           =  1,
        VERDE          =  2,
        CIANO          =  3,
        VERMELHO       =  4,
        MAGENTA        =  5,
        MARROM         =  6,
        CINZA_CLARO    =  7,
        CINZA_ESCURO   =  8,
        AZUL_CLARO     =  9,
        VERDE_CLARO    = 10,
        CIANO_CLARO    = 11,
        VERMELHO_CLARO = 12,
        MAGENTA_CLARO  = 13,
        AMARELO        = 14,
        BRANCO         = 15
    }
    Cor;

typedef
	enum Key
	{
        Cima         = 72,
        Esq          = 75,
        Baixo        = 80,
        Dir          = 77,
        BackSpace    = 8,
        Enter        = 13,
        PageUp       = 73,
        PageDown     = 81,
        Tecla        = 224
	}Key;


unsigned int minC ();
unsigned int minL ();
unsigned int maxC ();
unsigned int maxL ();

unsigned int cAtual ();
unsigned int lAtual ();

void vaParaCL (unsigned int col, unsigned int lin);

void limpaAteFimDaL ();
void limpaTela      ();

void apagaL  ();
void insereL ();

Cor  corDoTexto       ();
void ajustaCorDoTexto (Cor cor);

Cor  corDoFundo       ();
void ajustaCorDoFundo (Cor cor);

void someCursor ();
void voltaCursor ();

void escreva (char* fmt,...);

void setaDireita (ListaDeLinhas* listaDeLinhas,
                      int *x          , int *y,
                      int *xTelaInicio, int *xTelaFim,
                      int *yTelaInicio, int *yTelaFim,
                      int *xImaginario, int *yImaginario);

void setaEsquerda(ListaDeLinhas* listaDeLinhas,
                      int *x          , int *y,
                      int *xTelaInicio, int *xTelaFim,
                      int *yTelaInicio, int *yTelaFim,
                      int *xImaginario, int *yImaginario);

void setaCima    (ListaDeLinhas* listaDeLinhas,
                      int *x          , int *y,
                      int *xTelaInicio, int *xTelaFim,
                      int *yTelaInicio, int *yTelaFim,
                      int *xImaginario, int *yImaginario);

void setaBaixo   (ListaDeLinhas* listaDeLinhas,
                      int *x          , int *y,
                      int *xTelaInicio, int *xTelaFim,
                      int *yTelaInicio, int *yTelaFim,
                      int *xImaginario, int *yImaginario);


void verificarEscrita(ListaDeLinhas* listaDeLinhas,
                      int *x          , int *y,
                      int *xTelaInicio, int *xTelaFim,
                      int *yTelaInicio, int *yTelaFim,
                      int *xImaginario, int *yImaginario);


void backSpace(ListaDeLinhas* listaDeLinhas,
                      int *x          , int *y,
                      int *xTelaInicio, int *xTelaFim,
                      int *yTelaInicio, int *yTelaFim,
                      int *xImaginario, int *yImaginario);




void atualizarTela(ListaDeLinhas* listaDeLinhas,
                   int x          , int y,
                   int xTelaInicio, int xTelaFim,
                   int yTelaInicio, int yTelaFim,
                   int xImaginario, int yImaginario);

void armazenarCaracter(ListaDeLinhas* listaDeLinhas,
                       int *x          , int *y,
                       int *xTelaInicio, int *xTelaFim,
                       int *yTelaInicio, int *yTelaFim,
                       int *xImaginario, int *yImaginario,
                       char caracter);


void apagarTexto();




#endif
