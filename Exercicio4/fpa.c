//
// Created by leandrobf on 3/9/22.
//

#include "fpa.h"
#include <stdlib.h>


struct no{
    Paciente info;
    struct no *prox;
};


Fila cria_fila(){
    return NULL;
}


int fila_vazia(Fila f){
    if(f == NULL)
        return 1;
    else
        return 0;
}

int insere(Fila *f, Paciente elem) {
    Fila N = (Fila) malloc(sizeof(struct no));
    if (N == NULL) {return 0;}

    N->info = elem;

    if (fila_vazia(*f))
    {
        N->prox = N;
        *f = N;
    }
    else {
        Fila aux = *f;
        while (aux->prox != NULL && aux->prox->info.gravidade > elem.gravidade)
            aux = aux->prox;

        N->prox = aux->prox;
        aux->prox = N;
        *f = N;
    }

    return 1;
}

int remove_ini(Fila *f, Paciente *elem) {
    if (fila_vazia(*f))
        return 0;

    Fila aux = (*f)->prox;
    *elem = aux->info;

    if (*f == (*f)->prox)
        *f = NULL;
    else
        (*f)->prox = aux->prox;

    free(aux);
    return 1;
}

int apaga_fila(Fila *f) {
    if ((*f) == NULL)
        return 0;

    Fila aux = (*f)->prox;

    while (aux->prox != aux) {
        (*f)->prox = aux->prox;
        *f = aux->prox;
        free(aux);
        aux = *f;
    }

    free(aux);
    *F = NULL;

    return 1;
}

int esvazia_fila(Fila f){
    if (f == NULL)
        return 0;

    struct no *aux;

    while (f->ini != f->fim) {
        aux = f->ini;
        f->ini = aux->prox;
        free(aux);
    }

    f->ini = NULL;
    f->fim = NULL;
    return 1;
}


int tamanho_fila(Fila f){
    if(f == NULL)
        return -1;

    Fila f2 = cria_fila();
    Paciente t;

    int c = 0;

    while(!fila_vazia(f)) {
        remove_ini(&f, &t);
        insere_fim(f2, t);
        c++;
    }
    while(!fila_vazia(f2)) {
        remove_ini(&f2, &t);
        insere_fim(f, t);
    }

    return c;
}