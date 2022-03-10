/*
 * TAD Pilha
 * - Dados: inteiros
 * - Lista de Operações: cria_pilha, pilha_vazia, pilha_cheia, push, pop,
 *   get_topo, apaga_pilha, esvazia_pilha, tamanho_pilha
 */

#include "pilha.h"
#include <stdlib.h>
#include <string.h>

#define max 20

struct pilha {
    int vetor[max];
    int topo;
};

/*
 * Operação Cria_Pilha:
 * – Entrada: nenhuma
 * – Pré-condição: nenhuma
 * – Processo: cria uma pilha e a coloca no estado de pilha vazia
 * – Saída: endereço da pilha criada
 * – Pós-condição: nenhuma
 */

Pilha cria_pilha(){
    Pilha P;
    P = (Pilha) malloc(sizeof(Pilha));
    if (P != NULL)
        P->topo = -1;
    return P;
}

/*
 * Operação Pilha_Vazia:
 * – Entrada: endereço da pilha
 * – Pré-condição: nenhuma
 * – Processo: verifica se a pilha está vazia
 * – Saída: retorna 1 se pilha vazia ou 0 caso contrário
 * – Pós-condição: nenhuma
 */

int pilha_vazia(Pilha P){
    if (P->topo == -1) return 1;
    else return 0;
}

/*
 * Operação Pilha_Cheia:
 * – Entrada: endereço da pilha
 * – Pré-condição: nenhuma
 * – Processo: verifica se a pilha está cheia
 * – Saída: retorna 1 se pilha cheia ou 0 caso contrário
 * – Pós-condição: nenhuma
 */

int pilha_cheia(Pilha P){
    if (P->topo == max - 1)
        return 1;
    else return 0;
}

/*
 * Operação Empilha (push):
 * – Entrada: endereço da pilha e o elemento a ser inserido
 * – Pré-condição: pilha não estar cheia
 * – Processo: inserir o elemento informado no topo da pilha
 * – Saída: retorna 1 se a operação foi bem sucedida ou 0 caso contrário
 * – Pós-condição: a pilha de entrada com um elemento a mais
 */

int push(Pilha P, int elem){
    if (P == NULL || pilha_cheia(P)) return 0;

    P->topo++;
    P->vetor[P->topo] = elem;
    return 1;
}

/*
 * • Operação pop:
 * – Entrada: endereço da pilha e o endereço de retorno do elemento do topo da pilha
 * – Pré-condição: pilha não estar vazia
 * – Processo: remover o elemento que está no topo da pilha e retorná-lo
 * – Saída: retorna 1 se a operação foi bem sucedida ou 0 caso contrário
 * – Pós-condição: a pilha de entrada com um elemento a menos e a variável de retorno
 *   com o elemento removido
 */

int pop(Pilha P, int *elem){
    if (P == NULL || pilha_vazia(P)) return 0;

    *elem = P->vetor[P->topo];
    P->topo--;
    return 1;
}

/*
 * Operação Get_Topo:
 * – Entrada: endereço da pilha e o endereço de retorno do elemento do topo da pilha
 * – Pré-condição: pilha não estar vazia
 * – Processo: retornar o valor do elemento que está no topo da pilha SEM removê-lo
 * – Saída: retorna 1 se a operação foi bem sucedida ou 0 caso contrário
 * – Pós-condição: variável de retorno com o elemento do topo
 */

int get_topo(Pilha P, int *elem){
    if (P == NULL || pilha_vazia(P)) return 0;

    *elem = P->vetor[P->topo];
    return 1;
}

/*
 * Operação Apaga_Pilha:
 * – Entrada: endereço da pilha
 * – Pré-condição: pilha valida
 * – Processo: que elimina a pilha passada como entrada
 * – Saída: retorna 1 se a operação foi bem sucedida ou 0 caso contrário
 * – Pós-condição: pilha apagada
 */

int apaga_pilha(Pilha *P){
    if (P == NULL) return 0;

    free(*P);
    *P = NULL;

    return 1;
}

/*
 * Operação Esvazia_Pilha:
 * – Entrada: endereço da pilha
 * – Pré-condição: pilha valida
 * – Processo: esvazia a pilha passada como entrada
 * – Saída: retorna 1 se a operação foi bem sucedida ou 0 caso contrário
 * – Pós-condição: pilha em condição de vazia
 */

int esvazia_pilha(Pilha P){
    if (P == NULL) return 0;

    P->topo = -1;

    return 1;
}

/*
 * Operação Tamanho_Pilha:
 * – Entrada: endereço da pilha
 * – Pré-condição: pilha valida
 * – Processo: nenhuma
 * – Saída: retorna o tamanho da pilha
 * – Pós-condição: nenhuma
 */

int tamanho_pilha(Pilha P){
    if(P == NULL) return -1;
    return P->topo + 1;
}