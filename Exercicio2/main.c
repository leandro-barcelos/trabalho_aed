#include <stdio.h>
#include "pilha.h"

float avaliar(char *expressao);

int main() {
    avaliar("(AD)/B^F");
    return 0;
}

float avaliar(char expressao[]) {
    Pilha p_exp = cria_pilha();
    float valores[6] = {0};
    float t_valor;
    union tp_dado t_elem;

    for (int i = 0; expressao[i] != '\0'; i++) {
        t_elem.letra = expressao[i];
        push(&p_exp, 1, t_elem);

        if (expressao[i] == 'A' || expressao[i] == 'B' || expressao[i] == 'C' ||
            expressao[i] == 'D' || expressao[i] == 'E' || expressao[i] == 'F') {
            if (valores[expressao[i] - 65] == 0) {
                printf("Digite o valor para %c: ", expressao[i]);
                scanf("%f", &t_valor);
                valores[expressao[i] - 65] = t_valor;
            }
        }
    }
}