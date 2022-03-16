#ifndef EXERCICIO3_FILA_H
#define EXERCICIO3_FILA_H

#define MAX_STRING 30
#include <time.h>

typedef struct fila *Fila;

typedef struct carro {
    char placa[7];
    char tipo_servico;
    time_t hora_entrada;
} Carro;

Fila cria_fila();
int fila_vazia(Fila F);
int fila_cheia(Fila F);
int insere_fim(Fila *F, Carro elem);
int remove_ini(Fila *F, Carro *elem);
int apaga_fila(Fila *F);
int esvazia_fila(Fila *F);
int tamanho_fila(Fila F);

#endif //EXERCICIO3_FILA_H