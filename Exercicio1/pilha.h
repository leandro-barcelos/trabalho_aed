#ifndef EXERCICIO1_PILHA_H
#define EXERCICIO1_PILHA_H

typedef struct pilha *Pilha;

Pilha cria_pilha();
int pilha_vazia(Pilha P);
int pilha_cheia(Pilha P);
int push(Pilha P, int elem);
int pop(Pilha P, int *elem);
int get_topo(Pilha P, int *elem);
int apaga_pilha(Pilha *P);
int esvazia_pilha(Pilha P);
int tamanho_pilha(Pilha P);

#endif //EXERCICIO1_PILHA_H