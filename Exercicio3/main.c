#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fila.h"


void entrada(Fila *boxes);

void saida(Fila *boxes);

time_t simula_hora(time_t hora_entrada);

void visualizar_cenario(Fila *boxes);

int main() {
    Fila boxes[3];
    boxes[0] = cria_fila();
    boxes[1] = cria_fila();
    boxes[2] = cria_fila();

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
                entrada(boxes);
                printf("\n");
                break;
            case '2':
                saida(boxes);
                printf("\n");
                break;
            case '3':
                visualizar_cenario(boxes);
                printf("\n");
                break;
            default:
                apaga_fila(&boxes[0]);
                apaga_fila(&boxes[1]);
                apaga_fila(&boxes[2]);
                return 0;

        }
    }
}


void entrada(Fila *boxes) {
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

    int n_menor = 0;

    for (int i = 1; i < 3; i++) {
        if (tamanho_fila(boxes[i]) < tamanho_fila(boxes[n_menor]))
            n_menor = i;
    }
    if (fila_cheia(boxes[n_menor]) == 1) {
        printf("Todos os boxes estão cheios :(");
        return;
    }

    insere_fim(boxes[n_menor], elem);
    printf("Entrou no box %d", n_menor+1);
}

time_t simula_hora(time_t hora_entrada) {
    srand(time(NULL));
    int rand_hora = (rand() % 10) + 1;
    int rand_min = rand() % 60;

    hora_entrada += (rand_hora * 3600) + (rand_min * 60);

    return hora_entrada;
}

void saida(Fila *boxes) {
    Fila f_tmp = cria_fila();
    Carro c_tmp;
    Carro saindo;
    int achou = 0;
    char placa[8];

    printf(" --- Saida de Veículos ---\n");
    printf("Número da placa: ");
    scanf("%s", placa);

    for (int i = 0; i < 3; i++) {
        int tam = tamanho_fila(boxes[i]);
        for (int j = 0; j < tam; j++) {
            remove_ini(boxes[i], &c_tmp);
            if (strcmp(c_tmp.placa, placa) != 0)
                insere_fim(boxes[i], c_tmp);
            else {
                saindo = c_tmp;
                achou = 1;
                break;
            }
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
        struct tm tm_entrada, tm_saida;
        time_t hora_saida = simula_hora(saindo.hora_entrada);
        localtime_r(&saindo.hora_entrada, &tm_entrada);
        localtime_r(&hora_saida, &tm_saida);
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

        printf("Hora de entrada: %02d/%02d, %02d:%02d\n", tm_entrada.tm_mday, tm_entrada.tm_mon+1, tm_entrada.tm_hour, tm_entrada.tm_min);
        printf("Hora de saída: %02d/%02d, %02d:%02d\n", tm_saida.tm_mday, tm_saida.tm_mon+1, tm_saida.tm_hour, tm_saida.tm_min);
        printf("Valor a ser pago: R$%.2f\n", valor);
        printf("Volte sempre! :D\n\n");
    }
}

void visualizar_cenario(Fila *boxes) {
    int tam[3];
    tam[0] = tamanho_fila(boxes[0]);
    tam[1] = tamanho_fila(boxes[1]);
    tam[2] = tamanho_fila(boxes[2]);
    Carro c[3];
    char h_separator[] = "+---------+---------+---------+\n";

    printf("%s", h_separator);
    printf("|  Box1   |  Box2   |  Box3   |\n");
    printf("%s", h_separator);


    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            if (i < tam[j]) {
                remove_ini(boxes[j], &c[j]);
                insere_fim(boxes[j], c[j]);
            }
            else
                strcpy(c[j].placa, "       ");
        }

        printf("| %s | %s | %s |\n", c[0].placa, c[1].placa, c[2].placa);
    }

    printf("%s", h_separator);
}
