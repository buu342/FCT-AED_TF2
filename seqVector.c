#include <stdlib.h>
#include "iterador.h"
#include "sequencia.h"


/*===================================
           Global Variables
===================================*/

struct _sequencia
{
    void** elems;
    int numelems;
    int capacidade;
};


/*===================================
           criaSequencia
Allocate memory for sequence elements
===================================*/

sequencia criaSequencia(int cap)
{
    sequencia s;

    // Allocate memory for the sequence and make sure it works
    s=(sequencia) malloc(sizeof(struct _sequencia));
    if(s==NULL)
        return NULL;

    // Allocate memory for an element pointer and make sure it works
    s->elems = malloc(sizeof(void*) * cap);
    if (s->elems == NULL)
    {
        free(s);
        return NULL;
    }

    // Set the default values and return the sequence
    s->numelems=0;
    s->capacidade=cap;

    return s;
}


/*===================================
          destroiSequencia
  Free memory used by the sequence
===================================*/

void destroiSequencia(sequencia s)
{
    free(s->elems);
    free(s);
}


/*===================================
          destroiSequencia
Free memory used by the sequence and
            its elements
===================================*/

void destroiSeqElems(sequencia s, void (*destroi)(void *) )
{
    int i;

    for(i=0;i<s->numelems;i++)
        destroi(s->elems[i]);
    destroiSequencia(s);
}


/*===================================
           vaziaSequencia
   Check if the sequence is empty
===================================*/

int vaziaSequencia(sequencia s)
{
    return (s->numelems==0);
}


/*===================================
           tamanhoSequencia
   Return the size of the sequence
===================================*/

int tamanhoSequencia(sequencia s)
{
    return s->numelems;
}


/*===================================
         elementoPosSequencia
 Return the element in a position of
            the sequence
===================================*/


void* elementoPosSequencia(sequencia s, int i)
{
    void *elem=s->elems[i-1];
    return elem;
}


/*===================================
         adicionaPosSequencia
Add an element to the position of the
              sequence
===================================*/

void adicionaPosSequencia(sequencia s, void * elem, int i)
{
    int j;

    for(j=i; j<s->numelems; j++)
        s->elems[j-1]=s->elems[j];

    s->elems[i-1] = elem;
    s->numelems++;
}


/*===================================
         removePosSequencia
 Remove an element in a position of
            the sequence
===================================*/

void* removePosSequencia(sequencia s, int i)
{

    void* elemtoremove = s->elems[i-1];
    int j;

    for (j = i; j < s->numelems; j++)
        s->elems[j-1] = s->elems[j];

    s->numelems--;

    return elemtoremove;
}


/*===================================
          iteradorSequencia
 Create an iterator for the sequence
===================================*/

iterador iteradorSequencia(sequencia s)
{

    int i;
    void **aux = malloc(sizeof (void*) * s->numelems);

    for (i = 0; i < s->numelems; i++)
        aux[i] = s->elems[i];

    iterador it = criaIterador(aux, s->numelems);

    return it;
}
