/*
 * TAD Fila:
 * - Dados: Paciente
 * - Lista de Operações: cria_fila, fila_vazia, insere, remove_ini, apaga_fila, esvazia_fila, tamanho_fila
 */

#include "fpa.h"
#include <stdlib.h>


struct no{
    Paciente info;
    struct no *prox;
};

/*
 * Operação cria_fila:
 * - Entrada: nenhuma
 * - Pré-condição: nenhuma
 * - Processo: cria uma fila em condição de vazia
 * - Saída: Fila criada
 * - Pós-condição: nenhuma
 */

Fila cria_fila(){
    return NULL;
}

/*
 * Operação fila_vazia:
 * - Entrada: Fila
 * - Pré-condição: nenhuma
 * - Processo: verifica se a fila está em condição de vazia
 * - Saída: 1 (vazia) ou 0
 * - Pós-condição: nenhuma
 */

int fila_vazia(Fila f){
    if(f == NULL)
        return 1;
    else
        return 0;
}

/*
 * Operação insere:
 * - Entrada: Endereço da fila e elemento para inserir
 * - Pré-condição: nenhuma
 * - Processo: Insere o elemento na fila de acordo com sua prioridade
 * - Saída:  1 (sucesso), 0 (falha)
 * - Pós-condição: Fila com um elemento a mais
 */

int insere(Fila *f, Paciente elem) {
    Fila N = (Fila) malloc(sizeof(struct no));
    if (N == NULL) {return 0;}
    N->info = elem;

    if (fila_vazia(*f)) {
        N->prox = N;
        *f = N;
    }
    else if ((*f)->prox->info.gravidade > elem.gravidade) {
        N->prox = (*f)->prox;
        (*f)->prox = N;
    }
    else {
        Fila aux = (*f)->prox;
        while (aux->prox->info.gravidade < elem.gravidade && aux->prox != *f)
            aux = aux->prox;

        N->prox = aux->prox;


        if (aux->prox == *f) {
            aux->prox = N;
            *f = N;
        } else
            aux->prox = N;

    }

    return 1;
}

/*
 * Operação remove_ini:
 * - Entrada: Endereço da fila e endereço de elemento
 * - Pré-condição: Fila não vazia
 * - Processo: Remove o primeiro elemento
 * - Saída: 1 (sucesso), 0 (falha)
 * - Pós-condição: Fila com um elemento removido e endereço de elemento com o valor do elemento removido
 */

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

/*
 * Operação apaga_fila:
 * - Entrada: Endereço da fila
 * - Pré-condição: Fila não vazia
 * - Processo: Apaga a fila
 * - Saída: 1 (sucesso), 0 (falha)
 * - Pós-condição: Fila apagada
 */

int apaga_fila(Fila *f) {
    if (fila_vazia(*f))
        return 0;

    Fila aux = (*f)->prox;

    while (aux->prox != aux) {
        (*f)->prox = aux->prox;
        *f = aux->prox;
        free(aux);
        aux = *f;
    }

    free(aux);
    *f = NULL;

    return 1;
}

/*
 * Operação tamanho_fila:
 * - Entrada: Fila
 * - Pré-condição: nenhuma
 * - Processo: Perorre a fila e encontra seu tamanho
 * - Saída: Tamaho da fila
 * - Pós-condição: nenhuma
 */

int tamanho_fila(Fila f){
    if(f == NULL)
        return -1;

    Fila f2 = cria_fila();
    Paciente t;

    int c = 0;

    while(!fila_vazia(f)) {
        remove_ini(&f, &t);
        insere(&f2, t);
        c++;
    }
    while(!fila_vazia(f2)) {
        remove_ini(&f2, &t);
        insere(&f, t);
    }

    return c;
}