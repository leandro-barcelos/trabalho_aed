/*
 * TAD Fila
 * Dados: Carro
 * Lista de Operações: cria_fila, fila_vazia, fila_cheia, insere_fim, remove_ini
 */

#include <stdlib.h>
#include <string.h>
#include "fila.h"



#define MAX 5

struct fila {
    Carro vetor[MAX];
    int ini, cont;
};

/*
 * Operação cria_fila:
 * - Entrada: nenhuma
 * - Pré-Condição: nenhuma
 * - Processo: aloca as posições da fila e coloca no estado de vazia
 * - Saída: fila criada
 * - Pós-Condição: nenhuma
 */

Fila cria_fila() {
    Fila F;
    F = (Fila) malloc(sizeof(struct fila));

    if(F != NULL) {
        F->ini = 0;
        F->cont = 0;
    }

    return F;
}

/*
 * Operação fila_vazia:
 * - Entrada: Fila
 * - Pré-Condição: nenhuma
 * - Processo: verifica se a lista está no estado de vazia
 * - Saída: 1 (vazia) ou 0
 * - Pós-Condição: nenhuma
 */

int fila_vazia(Fila F) {
    if (F->cont == 0)
        return 1;
    else
        return 0;
}

/*
 * Operação fila_cheia:
 * - Entrada: Fila
 * - Pré-Condição: nenhuma
 * - Processo: verifica se a lista está no estado de cheia
 * - Saída: 1 (cheia) ou 0
 * - Pós-Condição: nenhuma
 */

int fila_cheia(Fila F) {
    if (F->cont == MAX)
        return 1;
    else
        return 0;
}

/*
 * Operação insere_fim:
 * - Entrada: Fila e elemento a ser inserido
 * - Pré-Condição: Fila não estar cheia
 * - Processo: insere o elemento no final da fila
 * - Saída: 1 (sucesso) ou 0 (falha)
 * - Pós-Condição: Fila com o elemento inserido
 */

int insere_fim(Fila *F, Carro elem) {
    if (fila_cheia(*F))
        return 0;

    (*F)->vetor[((*F)->ini+(*F)->cont) % MAX] = elem;
    (*F)->cont++;
    return 1;
}

/*
 * Operação remove_ini:
 * - Entrada: Fila e endereço de uma variável Aluno
 * - Pré-Condição: Fila não estar vazia
 * - Processo: remove o elemento do início da fila
 * - Saída: 1 (sucesso) ou 0 (falha)
 * - Pós-Condição: Fila com o elemento removido e variável
 *                 passada com o valor do elemento removido
 */

int remove_ini(Fila *F, Carro *elem) {
    if (fila_vazia(*F))
        return 0;

    *elem = (*F)->vetor[(*F)->ini];
    (*F)->ini = ((*F)->ini + 1) % MAX;
    (*F)->cont--;

    return 1;
}

/*
 * Operação apaga_fila:
 * - Entrada: Fila
 * - Pré-Condição: Fila válida
 * - Processo: elimina a fila passada
 * - Saída: 1 (sucesso) ou 0 (falha)
 * - Pós-Condição: Fila apagada
 */

int apaga_fila(Fila *F) {
    if (*F == NULL)
        return 0;

    free(*F);
    *F = NULL;

    return 1;
}

/*
 * Operação esvazia_fila:
 * - Entrada: Fila
 * - Pré-Condição: Fila válida
 * - Processo: retorna a fila passada ao estado de vazia
 * - Saída: 1 (sucesso) ou 0 (falha)
 * - Pós-Condição: Fila em estado de vazia
 */

int esvazia_fila(Fila *F){
    if (*F == NULL)
        return 0;

    (*F)->ini = 0;
    (*F)->cont = 0;

    return 1;
}

/*
 * Operação tamanho_fila:
 * - Entrada: Fila
 * - Pré-Condição: Fila válida
 * - Processo: nenhum
 * - Saída: tamanho da fila ou -1 (falha)
 * - Pós-Condição: nenhuma
 */

int tamanho_fila(Fila F){
    if (F == NULL)
        return -1;

    return F->cont;
}