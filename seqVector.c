#include <stdlib.h>
#include "iterador.h"
#include "sequencia.h"

// Definition of our sequence struct
struct _sequencia
{
    void** element; // apontador para vector de enderecos de elementos
    int numElements;
    int size; // capacidade corrente do vector
};


sequencia criaSequencia(int capacity)
{
    // Allocate memory for the sequence
    sequencia seq = malloc(sizeof(struct _sequencia));

    // Check if it was created sucessfully.
    if (seq == NULL) 
        return NULL;

    seq->element = NULL;
    seq->numElements = 0;
    seq->size = capacity;
    
    return seq;
}


void destroiSequencia(sequencia s)
{
    //Fazer
}


void destroiSeqElems(sequencia s, void (*destroi)(void *))
{
    //Fazer
}


int vaziaSequencia(sequencia s)
{
    //Fazer
    return 0;
}


int tamanhoSequencia(sequencia s)
{
    //Fazer
    return 0;
}


void* elementoPosSequencia(sequencia s, int i)
{
    //Fazer
}


void adicionaPosSequencia(sequencia s, void * elem, int i)
{
    //Fazer
}


void* removePosSequencia(sequencia s, int i)
{
    //Fazer
}


iterador iteradorSequencia(sequencia s)
{
    //CUIDADO: DEVE DAR AO ITERADOR UMA COPIA DO VECTOR A PERCORRER
    //Fazer
}