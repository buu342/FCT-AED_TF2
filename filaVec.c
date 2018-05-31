/*
 * filaVec.c
 */
#include <stdlib.h>

#include "fila.h"

/* Estrutura de dados: fila ---> comportamento “Primeiro a chegar, Primeiro a sair” */
struct _fila{
    void ** elems;
    int numElems;
    int capacidade;
};

fila criaFila(int cap){
    fila f = (fila) malloc(sizeof(struct _fila));
    if (f == NULL) return NULL;
    f->elems = malloc(sizeof(void *)*cap);
    if (f->elems == NULL){
        free(f);
        return NULL;
    }
    f->capacidade = cap;
    f->numElems = 0;
    return f;
}


void destroiFila (fila f ){
    free(f->elems);
    free(f);
}

void destroiFilaEElems(fila f, void (*destroi)(void *) ){
    int i = 0;
    for(;i<f->numElems;i++)
        destroi(f->elems[i]);
    free(f->elems);
    free(f);
}

int vaziaFila(fila f){
    if (f->numElems == 0)
        return 1;
    return 0;
}

int tamanhoFila(fila f){
    return f->numElems;
}

void * elementoFila(fila f){
    return f->elems[0];
}
/* Aumenta o vector da fila */
void incFila (fila f){
    int i = 0;
    void ** aux = malloc(sizeof(void * ) * f->capacidade*2); // duplica
    for (;i<f->numElems;i++)
        aux[i] = f->elems[i];
    free(f->elems);
    f->elems = aux;
    f->capacidade = f->capacidade * 2;
}

void adicionaElemFila(fila f, void * elem){
    if (f->capacidade == f->numElems)
        incFila(f);
    f->elems[f->numElems++] = elem;
}

void * removeElemFila(fila f){
    int i = 0;
    void * aux = f->elems[0];
    f->numElems--;
    for(;i<f->numElems;i++)
        f->elems[i] = f->elems[i+1];
    return aux;
}

