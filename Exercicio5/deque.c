#include "deque.h"
#include <stdlib.h>
#include <string.h>

#define MAX_ELEM 10
#define MAX_CHAR 21

struct deque {
    char no[MAX_ELEM][MAX_CHAR];
    int ini;
    int fim;
};

/*
Operação: cria_deque
    -Entrada: nenhuma
    -Pré-condição: nenhuma
    -Processo: cria um deque e o coloca no estado de vazio
    -Saída: endereço do deque criado
    -Pós-condição: nenhuma
*/
Deque cria_deque() {
    Deque d;
    d = (Deque) malloc(sizeof(struct deque));
    if (d != NULL) {
        d->ini = MAX_ELEM - 1;
        d->fim = MAX_ELEM - 1;
    }
    return d;
}

/*
Operação: deque_vazio
    -Entrada: endereço do deque
    -Pré-condição: nenhuma
    -Processo: verifica se o deque está vazio
    -Saída: 1 se o deque estiver vazio ou 0 caso contrário
    -Pós-condição: nenhuma
*/
int deque_vazio(Deque d) {
    if (d == NULL)
        return 0;
    if (d->ini == d->fim)
        return 1;
    else
        return 0;
}

/*
Operação: deque_cheio
    -Entrada: endereço do deque
    -Pré-condição: nenhuma
    -Processo: verifica se o deque está cheio
    -Saída: 1 se o deque estiver cheio ou 0 caso contrário
    -Pós-condição: nenhuma
*/
int deque_cheio(Deque d) {
    if (d == NULL)
        return 0;
    if (d->ini == (d->fim+1)%MAX_ELEM)
        return 1;
    else
        return 0;
}

/*
Operação: insere_final
    -Entrada: endereço do deque e o elemento a ser inserido
    -Pré-condição: deque não estar cheio
    -Processo: inserir o elemento informado no final do deque
    -Saída: 1 - sucesso ou 0 - falha
    -Pós-condição: o deque de entrada com um elemento a mais
*/
int insere_final(Deque d, const char *elem) {
    if (d == NULL || deque_cheio(d) == 1)
        return 0;

    char *c = memchr(elem, '\0', MAX_CHAR);
    if (c == NULL)
        return 0;
    
    d->fim = (d->fim+1)%MAX_ELEM;
    strcpy(d->no[d->fim], elem);

    return 1;
}

/*
Operação: insere_inicio
    -Entrada: endereço do deque e o elemento a ser inserido
    -Pré-condição: deque não estar cheio
    -Processo: inserir o elemento informado no inicio do deque
    -Saída: 1 - sucesso ou 0 - falha
    -Pós-condição: o deque de entrada com um elemento a mais
*/
int insere_inicio(Deque d, const char *elem) {
    if (d == NULL || deque_cheio(d) == 1)
        return 0;

    char *c = memchr(elem, '\0', MAX_CHAR);
    if (c == NULL)
        return 0;
    
    strcpy(d->no[d->ini], elem);
    d->ini = (d->ini-1)%MAX_ELEM;

    return 1;
}

/*
Operação: remove_inicio
    -Entrada: endereço do deque e o endereço de retorno do elemento removido
    -Pré-condição: deque não estar vazio
    -Processo: remover o elemento que está no início do deque e retornar seu valor
    -Saída: 1 - sucesso ou 0 - falha
    -Pós-condição: o deque de entrada com um elemento a menos
*/
int remove_inicio(Deque d, char *elem) {
    if (d == NULL || deque_vazio(d) == 1)
        return 0;
    
    d->ini = (d->ini+1)%MAX_ELEM;
    strcpy(elem, d->no[d->ini]);

    return 1;
}

/*
Operação: remove_final
    -Entrada: endereço do deque e o endereço de retorno do elemento removido
    -Pré-condição: deque não estar vazio
    -Processo: remover o elemento que está no final do deque e retornar seu valor
    -Saída: 1 - sucesso ou 0 - falha
    -Pós-condição: o deque de entrada com um elemento a menos
*/
int remove_final(Deque d, char *elem) {
    if (d == NULL || deque_vazio(d) == 1)
        return 0;
    
    strcpy(elem, d->no[d->fim]);
    d->fim = (d->fim-1)%MAX_ELEM;

    return 1;
}

/*
Operação: apaga_deque
    -Entrada: endereço do endereço do deque
    -Pré-condição: deque ser válido
    -Processo: libera o espaço de memória ocupado pelo deque e faz ele apontar para NULL
    -Saída: 1 - sucesso ou 0 - falha
    -Pós-condição: deque apagado
*/
int apaga_deque(Deque *d) {
    if (*d == NULL)
        return 0;
    
    free(*d);
    *d = NULL;
    return 1;
}

/*
Operação: esvazia_deque
    -Entrada: endereço do deque
    -Pré-condição: deque não estar vazio
    -Processo: reinicializa o início e o final, tornando o deque vazio
    -Saída: 1 - sucesso ou 0 - falha
    -Pós-condição: deque vazio
*/
int esvazia_deque(Deque d) {
    if (d == NULL || deque_vazio(d) == 1)
        return 0;
    
    d->ini = MAX_ELEM-1;
    d->fim = MAX_ELEM-1;
    return 1;
}

/*
Operação: tamanho_deque
    -Entrada: endereço do deque
    -Pré-condição: deque ser válido
    -Processo: retorna o tamanho do deque
    -Saída: o tamanho do deque ou -1 caso o deque for inválido
    -Pós-condição: nenhuma
*/
int tamanho_deque(Deque d) {
    if (d == NULL)
        return -1;
    if (deque_vazio(d) == 1)
        return 0;
    
    if (d->fim > d->ini)
        return d->fim - d->ini;
    else
        return d->fim + (MAX_ELEM - d->ini);
}
