#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fila.h"

Fila box[3];

void entrada();

void saida();

time_t simula_hora(time_t hora_entrada);

void visualizar_cenario();

int main() {
    char escolha = '4';

    while (1) {
        printf("--- Estacionamento ---\n");
        printf("Opcoes:\n");
        printf("1 - Entrar com veículo\n");
        printf("2 - Sair com veículo\n");
        printf("3 - Visualizar estacionamento\n");
        printf("4 - Sair\n");
        printf("-> ");
        scanf(" %c", &escolha);

        switch (escolha) {
            case '1':
                entrada();
                break;
            case '2':
                saida();
                break;
            case '3':
//                visualizar_cenario();
                break;
            case '4':
                return 0;

        }
    }
}


void entrada() {
    Carro elem;
    char placa[8];
    char servico;
    time_t hora_atual;

    printf(" --- Entrada de Veículos ---\n");
    printf("Número da placa: ");
    scanf("%s", placa);
    strcpy(elem.placa, placa);

    printf("Tipo de Servico (A - Avulso, M - Mensal): ");
    scanf(" %c", &servico);
    elem.tipo_servico = servico;

    time(&hora_atual);
    elem.hora_entrada = hora_atual;

    int menor;

    if (tamanho_fila(box[0]) <= tamanho_fila(box[1]) &&
        tamanho_fila(box[0]) <= tamanho_fila(box[2])) {
        menor = 0;
    }
    else if (tamanho_fila(box[1]) <= tamanho_fila(box[0]) &&
             tamanho_fila(box[1]) <= tamanho_fila(box[2])) {
        menor = 1;
    }
    else if (tamanho_fila(box[2]) <= tamanho_fila(box[0]) &&
             tamanho_fila(box[2]) <= tamanho_fila(box[1]))  {
        menor = 2;;
    }
    else {
        printf("Todos os boxes estao cheios :(");
        return;
    }

    insere_fim(&box[menor], elem);
    printf("Entrou no box %d", menor + 1);
}

time_t simula_hora(time_t hora_entrada) {
    srand(time(NULL));
    int rand_hora = (rand() % 10) + 1;
    int rand_min = rand() % 60;

    hora_entrada += (rand_hora * 3600) + (rand_min * 60);

    return hora_entrada;
}

void saida() {
    Fila f_tmp;
    Carro c_tmp;
    Carro saindo;
    int achou = 0;
    char placa[8];

    printf(" --- Saida de Veículos ---\n");
    printf("Número da placa: ");
    scanf("%s", placa);

    for (int i = 0; i < 3; i++) {
        while (!fila_vazia(box[i])) {
            remove_ini(&box[i], &c_tmp);
            if (strcmp(c_tmp.placa, placa) != 0)
                insere_fim(&f_tmp, c_tmp);
            else {
                saindo = c_tmp;
                achou = 1;
            }
        }
        while (!fila_vazia(f_tmp)) {
            remove_ini(&f_tmp, &c_tmp);
            insere_fim(&box[i], c_tmp);
        }

        if (achou)
            break;
    }

    if (!achou) {
        printf("Placa digitada nao esta no estacionamento! :O");
        return;
    }

    if (saindo.tipo_servico == 'M') {
        printf("'Ja ta pago carissimo' Macedo, Autran - 2021 :)");
    }
    else {
        time_t hora_saida = simula_hora(saindo.hora_entrada);
        float valor = 0;

        time_t intervalo = hora_saida - saindo.hora_entrada;

        intervalo -= 3600;
        valor += 7;

        while (intervalo > 0) {
            if (intervalo > 3600){
                valor += 1;
                intervalo -= 3600;
            } else if(intervalo > 600) {
                valor += 1;
                intervalo = 0;
            } else
                intervalo = 0;
        }

        printf("Valor a ser pago: R$%.2f", valor);
        printf("Volte sempre! :D\n\n");

    }
}