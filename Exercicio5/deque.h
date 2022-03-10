#ifndef DEQUE_H
#define DEQUE_H

typedef struct deque * Deque;

Deque cria_deque();
int deque_vazio(Deque f);
int deque_cheio(Deque f);
int insere_final(Deque f, const char *elem);
int insere_inicio(Deque f, const char *elem);
int remove_inicio(Deque f, char *elem);
int remove_final(Deque f, char *elem);
int apaga_deque(Deque *f);
int esvazia_deque(Deque f);
int tamanho_deque(Deque f);

#endif
