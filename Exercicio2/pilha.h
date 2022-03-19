#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

union tp_dado {
    float num;
    char letra;
};

typedef struct no *Pilha;

Pilha cria_pilha();
int pilha_vazia (Pilha p);
int push (Pilha *p,int tipo, union tp_dado Dado );
int pop (Pilha *p, int *tipo, union tp_dado *Dado );
int get_topo (Pilha *p, int *tipo, union tp_dado *Dado);
int esvazia_pilha(Pilha *p);
int apaga_pilha(Pilha *p);

#endif // PILHA_H_INCLUDED