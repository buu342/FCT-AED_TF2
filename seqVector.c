#include <stdlib.h>
#include "iterador.h"
#include "sequencia.h"

struct _sequencia
{
    void** elems;
    int numelems;
    int capacidade;
};


sequencia criaSequencia(int cap)
{
    sequencia s;

    s=(sequencia) malloc(sizeof(struct _sequencia));
    if(s==NULL)
        return NULL;

    s->elems = malloc(sizeof(void*) * cap);
    if (s->elems == NULL)
    {
        free(s);
        return NULL;
    }

    s->numelems=0;
    s->capacidade=cap;

    return s;
}

void destroiSequencia(sequencia s)
{
    free(s->elems);
    free(s);
}

void destroiSeqElems(sequencia s, void (*destroi)(void *) )
{
    int i;

    for(i=0;i<s->numelems;i++)
        destroi(s->elems[i]);
    destroiSequencia(s);
}

int vaziaSequencia(sequencia s)
{
    return (s->numelems==0);
}

int tamanhoSequencia(sequencia s)
{
    return s->numelems;
}

void* elementoPosSequencia(sequencia s, int i)
{
    void *elem=s->elems[i-1];
    return elem;
}

void adicionaPosSequencia(sequencia s, void * elem, int i)
{
    int j;

    for(j=i; j<s->numelems; j++)
        s->elems[j-1]=s->elems[j];

    s->elems[i-1] = elem;
    s->numelems++;
}

void* removePosSequencia(sequencia s, int i)
{

    void* elemtoremove = s->elems[i-1];
    int j;

    for (j = i; j < s->numelems; j++)
        s->elems[j-1] = s->elems[j];

    s->numelems--;

    return elemtoremove;
}

iterador iteradorSequencia(sequencia s)
{

    int i;
    void **aux = malloc(sizeof (void*) * s->numelems);

    for (i = 0; i < s->numelems; i++)
        aux[i] = s->elems[i];

    iterador it = criaIterador(aux, s->numelems);

    return it;
}
