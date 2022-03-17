#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fila.h"


void entrada(Fila *box1, Fila *box2, Fila *box3);

void saida(Fila *box1, Fila *box2, Fila *box3);

time_t simula_hora(time_t hora_entrada);

void visualizar_cenario(Fila box1, Fila box2, Fila box3);

int main() {
    Fila box1 = cria_fila();
    Fila box2 = cria_fila();
    Fila box3 = cria_fila();

    char escolha = '4';

    while (1) {
        printf("--- Estacionamento ---\n");
        printf("Opções:\n");
        printf("1 - Entrar com veículo\n");
        printf("2 - Sair com veículo\n");
        printf("3 - Visualizar estacionamento\n");
        printf("4 - Sair\n");
        printf("-> ");
        scanf(" %c", &escolha);

        switch (escolha) {
            case '1':
                entrada(&box1, &box2, &box3);
                printf("\n");
                break;
            case '2':
                saida(&box1, &box2, &box3);
                printf("\n");
                break;
            case '3':
                visualizar_cenario(box1, box2, box3);
                printf("\n");
                break;
            default:
                apaga_fila(&box1);
                apaga_fila(&box2);
                apaga_fila(&box3);
                return 0;

        }
    }
}


void entrada(Fila *box1, Fila *box2, Fila *box3) {
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

    Fila f_menor;
    char n_menor;

    if (tamanho_fila(*box1) <= tamanho_fila(*box2) &&
        tamanho_fila(*box1) <= tamanho_fila(*box3)) {
        f_menor = *box1;
        n_menor = '1';
    }
    else if (tamanho_fila(*box2) <= tamanho_fila(*box1) &&
             tamanho_fila(*box2) <= tamanho_fila(*box3)) {
        f_menor = *box2;
        n_menor = '2';
    }
    else if (tamanho_fila(*box3) <= tamanho_fila(*box1) &&
             tamanho_fila(*box3) <= tamanho_fila(*box2))  {
        f_menor = *box3;
        n_menor = '3';
    }
    else {
        printf("Todos os boxes estão cheios :(");
        return;
    }

    insere_fim(&f_menor, elem);
    printf("Entrou no box %c", n_menor);
}

time_t simula_hora(time_t hora_entrada) {
    srand(time(NULL));
    int rand_hora = (rand() % 10) + 1;
    int rand_min = rand() % 60;

    hora_entrada += (rand_hora * 3600) + (rand_min * 60);

    return hora_entrada;
}

void saida(Fila *box1, Fila *box2, Fila *box3) {
    Fila f_tmp = cria_fila();
    Carro c_tmp;
    Carro saindo;
    int achou = 0;
    char placa[8];

    printf(" --- Saida de Veículos ---\n");
    printf("Número da placa: ");
    scanf("%s", placa);

    Fila *aux[] = {box1, box2, box3};

    for (int i = 0; i < 3; i++) {
        while (!fila_vazia(*aux[i])) {
            remove_ini(aux[i], &c_tmp);
            if (strcmp(c_tmp.placa, placa) != 0)
                insere_fim(&f_tmp, c_tmp);
            else {
                saindo = c_tmp;
                achou = 1;
            }
        }
        while (!fila_vazia(f_tmp)) {
            remove_ini(&f_tmp, &c_tmp);
            insere_fim(aux[i], c_tmp);
        }

        if (achou)
            break;
    }

    if (!achou) {
        printf("Placa digitada nao esta no estacionamento! :O");
        return;
    }

    if (saindo.tipo_servico == 'M') {
        printf("'Ja ta pago caríssimo' Macedo, Autran - 2021 :)");
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

        printf("Valor a ser pago: R$%.2f\n", valor);
        printf("Volte sempre! :D\n\n");

    }
}

void visualizar_cenario(Fila box1, Fila box2, Fila box3) {
    Fila f1 = cria_fila();
    Fila f2 = cria_fila();
    Fila f3 = cria_fila();
    Carro c1, c2, c3;
    char h_separator[] = "+---------+---------+---------+\n";

    printf("%s", h_separator);
    printf("|  Box1   |  Box2   |  Box3   |\n");
    printf("%s", h_separator);


    for (int i = 0; i < 5; i++) {
        if (remove_ini(&box1, &c1))
            insere_fim(&f1, c1);
        else
            strcpy(c1.placa, "       ");

        if (remove_ini(&box2, &c2))
            insere_fim(&f2, c2);
        else
            strcpy(c2.placa, "       ");

        if (remove_ini(&box3, &c3))
            insere_fim(&f3, c3);
        else
            strcpy(c3.placa, "       ");

        printf("| %s | %s | %s |\n", c1.placa, c2.placa, c3.placa);
    }

    while (!fila_vazia(f1) || !fila_vazia(f2) || !fila_vazia(f3)) {
        if (remove_ini(&f1, &c1))
            insere_fim(&box1, c1);

        if (remove_ini(&f2, &c2))
            insere_fim(&box2, c2);

        if (remove_ini(&f3, &c3))
            insere_fim(&box3, c3);
    }


    printf("%s", h_separator);
}