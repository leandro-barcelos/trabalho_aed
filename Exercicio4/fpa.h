#ifndef EXERCICIO4_FPA_H
#define EXERCICIO4_FPA_H

typedef struct paciente{
    int idade;
    char nome[10];
    char doenca, gravidade;
    float peso, altura;
}Paciente;

typedef struct no *Fila;

Fila cria_fila();
int fila_vazia(Fila f);
int insere(Fila *f, Paciente elem);
int remove_ini(Fila *f, Paciente *elem);
int apaga_fila(Fila *f);
int tamanho_fila(Fila F);

#endif //EXERCICIO4_FPA_H
