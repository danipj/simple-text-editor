#ifndef LISTADUPLA
#define LISTADUPLA

struct no
{
    char  info;
    struct
            no *proximo,
            *anterior;
};
typedef struct no No;

struct lista
{
    int tamanho;
    No *inicio,
    *fim;
};
typedef struct lista Lista;

Lista* create(Lista *lista);
void writeC (Lista *lista, int ind, char c);
char readC  (Lista *lista, int ind);
char erase (Lista *lista, int ind);

int getTamanho(Lista *lista);


#endif
