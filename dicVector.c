/*
 * dicVector.c
 */
#include <stdlib.h>
#include "iterador.h"
#include "dicionario.h"
#include "chaves.h"
#include "tuplo.h"

/*  Estrutura de dados do tipo de dados: dicionario ---> os elementos nao podem ser repetidos com base num identificador (chave) dos elementos */
struct _dicionario{
    tuplo * elems; // apontador para vector de tuplos (chave,elemento)
    int numElems;
    int capacidade;
    int tipoCh; // 0-inteiro; 1-string
};

dicionario criaDicionario(int cap, int tipoChave){
    dicionario d;
    d = (dicionario) malloc(sizeof(struct _dicionario));
    if ( d == NULL) return NULL;
    d->elems = (tuplo *) malloc(sizeof(tuplo) * cap);
    if (d->elems == NULL){
        free(d);
        return NULL;
    }
    d->numElems = 0;
    d->capacidade = cap;
    d->tipoCh =tipoChave;
    return d;
}

void destroiDicionario (dicionario d ){
    int i;
    for(i=0;i<d->numElems;i++)
        destroiTuplo(d->elems[i]);
    free(d->elems);
    free(d);
}

void destroiDicEElems(dicionario d, void (*destroi)(void *) ){
    int i;
    for(i=0;i < d->numElems;i++){
        destroi(segTuplo(d->elems[i]));
        destroiTuplo(d->elems[i]);
    }
    free(d->elems);
    free(d);
}

int vazioDicionario(dicionario d){
    if (d->numElems == 0)
        return 1;
    return 0;
}

int tamanhoDicionario(dicionario d){
    return d->numElems;
}

int posElemDicionario(dicionario d, void * ch){
    int i;
    for (i = 0; i<d->numElems;i++)
        if (igualChaves(ch,priTuplo(d->elems[i]),d->tipoCh) == 1)
            return i;
    return -1;
}
int existeElemDicionario(dicionario d, void * ch){
    if (posElemDicionario(d,ch) != -1)
        return 1;
    return 0;
}

void * elementoDicionario(dicionario d, void * ch){
    int pos = posElemDicionario(d,ch);
    if (pos != -1)
        return segTuplo(d->elems[pos]);
    return NULL;
}
/* Aumenta o vector do dicionario */
void incDicionario (dicionario d){
    int i = 0;
    tuplo* aux = (tuplo *)malloc(sizeof(tuplo) * d->capacidade*2); // duplica
    for (;i<d->numElems;i++)
        aux[i] = d->elems[i];
    free(d->elems);
    d->elems = aux;
    d->capacidade = d->capacidade * 2;
}

int adicionaElemDicionario(dicionario d, void * ch, void * elem){
    int pos = posElemDicionario(d,ch);
    if (pos != -1)
        return 0;
    if (d->numElems == d->capacidade)
        incDicionario(d);
    d->elems[d->numElems++] = criaTuplo(d->tipoCh,ch,elem);
    return 1;
}

void * removeElemDicionario(dicionario d, void * ch){
    void * elem;
    int pos = posElemDicionario(d,ch);
    if (pos == -1)
        return NULL;
    elem = segTuplo(d->elems[pos]);
    destroiTuplo(d->elems[pos]);
    d->elems[pos] = d->elems[--d->numElems];
    return elem;
}

iterador iteradorDicionario(dicionario d){
    int i;
    // vector com os elementos do dicionário
    void * * aux = (void * *) malloc(sizeof(void *)* d->numElems);
    for(i=0;i<d->numElems;i++)
        aux[i]=segTuplo(d->elems[i]);
    return criaIterador(aux,d->numElems);
}

iterador iteradorChaveDicionario(dicionario d){

    int i;
    // vector com as chaves dos elementos do dicionário
    void * * aux = (void * *) malloc(sizeof(void *)* d->numElems);
    for(i=0;i<d->numElems;i++)
        aux[i]=priTuplo(d->elems[i]);
    return criaIterador(aux,d->numElems);
}
