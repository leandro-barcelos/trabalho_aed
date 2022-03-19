#include "pilha.h"
#include <stdlib.h>

typedef struct {
    union tp_dado dado;
    int tipo;
} Dado;

struct no {
    Dado info;
    struct no* prox;
};

Pilha cria_pilha(){
    return NULL;
}

int pilha_vazia (Pilha p) {
    if (p == NULL)
        return 1;
    else
        return 0;
}

int push (Pilha *p,int tipo, union tp_dado Dado ){

    Pilha N = (Pilha) malloc(sizeof(struct no));
    if (N == NULL)
        return 0;

    N->info.tipo = tipo;

    if(tipo == 0){
        N->info.dado.num = Dado.num;
    }

    else if(tipo == 1){
        N->info.dado.letra = Dado.letra;
    }
    else{
        return 0;
    }

    N->prox = *p;
    *p = N;
    return 1;
}

int pop (Pilha *p, int *tipo, union tp_dado *Dado ) {
    if (pilha_vazia(*p) == 1)
        return 0;

    Pilha aux = *p;
    if(aux->info.tipo==0){
        (*Dado).num = aux->info.dado.num;

    }
    else if(aux->info.tipo==1){
        (*Dado).letra = aux->info.dado.letra;
    }
    (*tipo) =aux->info.tipo;
    *p = aux->prox;
    free(aux);
    return 1;
}

int get_topo (Pilha *p, int *tipo, union tp_dado *Dado) {
    if (pilha_vazia(*p) == 1)
        return 0;

    *tipo=(*p)->info.tipo;
    if((*p)->info.tipo==0){
        (*Dado).num = (*p)->info.dado.num;

    }
    else if((*p)->info.tipo==1){
        (*Dado).letra = (*p)->info.dado.letra;
    }

    return 1;
}

int esvazia_pilha(Pilha *p){
    if((*p) == NULL){
        return 0;}
    Pilha aux;
    while(*p != NULL){
        aux = *p;
        *p = aux->prox;
        free(aux);
    }
    return 1;
}

int apaga_pilha(Pilha *p){
    if(*p == NULL)
        return 0;
    Pilha aux;
    while(*p != NULL){
        aux = *p;
        *p = aux->prox;
        free(aux);
    }
    *p = NULL;
    return 1;
}
