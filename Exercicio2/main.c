#include "pilha.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

int validar(Pilha *p, const char *expr);
int converter(Pilha *p, const char *in, char *out);
int avaliar(Pilha *p, const char *expr, float *resultado);
int precedencia(char a, char b);

int main () {
    Pilha p = cria_pilha();
    char expr[50];
    char postfix[50];
    float resultado;
    int ret;

    while (1) {
        printf("Calculadora de expressoes matematicas\n");
        printf("-------------------------------------\n");
        printf("Digite a expressao: ");
        scanf("%s", expr);
        if (strcmp(expr, "FIM") == 0) {
            printf("\nFim do programa!\n");
            return 0;
        }
        ret = validar(&p, expr);
        switch (ret) {
            case 0:
                break;
            case 1:
                printf("Erro: precedencia entre delimitadores invalida\n\n");
                continue;
            case 2:
                printf("Erro: ordem do fechamento diverge da abertura\n\n");
                continue;
            case 3:
                printf("Erro: excesso de fechamentos\n\n");
                continue;
            case 4:
                printf("Erro: excesso de aberturas\n\n");
                continue;
            case 5:
                printf("Erro: caractere invalido encontrado\n\n");
                continue;
        }
        ret = converter(&p, expr, postfix);
        if (ret == 0) {
            printf("Erro ao converter expressao\n\n");
            continue;
        }
        printf("Expressao na forma pos-fixa: %s\n", postfix);
        ret = avaliar(&p, postfix, &resultado);
        switch (ret) {
            case 0:
                break;
            case 1:
            case 2:
                printf("Erro: falta de operandos ou excesso de operadores\n\n");
                continue;
            case 3:
                printf("Erro: falta de operadores ou excesso de operandos\n\n");
                continue;
            case 4:
                printf("Erro: caractere invalido encontrado\n\n");
                continue;
        }
        printf("Resultado da expressao: %.2f\n\n", resultado);
    }

    apaga_pilha(&p);

    return 0;
}

/*
    ret: 0: sucesso
         1: erro precedencia
         2: erro correspondencia
         3: erro fechado demais
         4: erro aberto demais
         5: caractere invalido
*/
int validar(Pilha *p, const char *expr) {
    apaga_pilha(p);
    union tp_dado dado;
    int tipo;

    for (int i = 0; expr[i] != '\0'; i++) {
        switch (expr[i]) {
            case 'A': case 'B': case 'C':
            case 'D': case 'E': case 'F':
            case '+': case '-': case '/':
            case '*': case '^': {
                break;
            }

            case '(': case '[': case '{': {
                if (pilha_vazia(*p) == 0) {
                    get_topo(p, &tipo, &dado);
                    if (expr[i] > dado.letra)
                        return 1;
                }
                dado.letra = expr[i];
                push(p, 1, dado);

                break;
            }

            case ')': case ']': case '}': {
                if (pilha_vazia(*p) == 1)
                    return 3;
                pop(p, &tipo, &dado);
                if ((expr[i] == ')' && dado.letra != '(')
                    || (expr[i] == ']' && dado.letra != '[')
                    || (expr[i] == '}' && dado.letra != '{'))
                    return 2;
                
                break;
            }

            default: {
                return 5;
            }
        }
    }

    if (pilha_vazia(*p) == 0)
        return 4;
    else
        return 0;
}

int converter(Pilha *p, const char *in, char *out) {
    apaga_pilha(p);
    int cont = 0;
    int tipo;
    union tp_dado dado;

    for (int i = 0; in[i] != '\0'; i++) {
        switch(in[i]) {
            case 'A': case 'B': case 'C':
            case 'D': case 'E': case 'F': {
                out[cont] = in[i];
                cont++;
                break;
            }

            case '^': case '*': case '/':
            case '+': case '-': {
                while (pilha_vazia(*p) == 0) {
                    get_topo(p, &tipo, &dado);
                    if (precedencia(dado.letra, in[i]) == 0)
                        break;
                    pop(p, &tipo, &dado);
                    out[cont] = dado.letra;
                    cont++;
                }
                dado.letra = in[i];
                push(p, 1, dado);

                break;
            }

            case '{': case '[': case '(': {
                dado.letra = in[i];
                push(p, 1, dado);

                break;
            }

            case '}': case ']': case ')': {
                while (pilha_vazia(*p) == 0) {
                    pop(p, &tipo, &dado);
                    if (dado.letra == '{' || dado.letra == '[' || dado.letra == '(')
                        break;
                    out[cont] = dado.letra;
                    cont++;
                }

                break;
            }

            default:
                return 0;
        }
    }

    while (pilha_vazia(*p) == 0) {
        pop(p, &tipo, &dado);
        out[cont] = dado.letra;
        cont++;
    }
    out[cont] = '\0';

    return 1;
}

/*
    ret: -1: operador inválido
         0: a tem prioridade menor que b
         1: a tem prioridade maior ou igual a b
*/
int precedencia(char a, char b) {
    int prec_a = 0;
    int prec_b = 0;

    switch (a) {
        case '^':
        prec_a++;
        case '*': case '/':
        prec_a++;
        case '+': case '-':
        prec_a++;
        case '{': case '[': case '(':
        prec_a++;
        break;
        default:
        return -1;
    }
    switch (b) {
        case '^':
        prec_b++;
        case '*': case '/':
        prec_b++;
        case '+': case '-':
        prec_b++;
        case '{': case '[': case '(':
        prec_b++;
        break;
        default:
        return -1;
    }

    if (prec_a >= prec_b)
        return 1;
    else
        return 0;
}

int avaliar(Pilha *p, const char *expr, float *resultado) {
    apaga_pilha(p);
    struct {
        int flag;
        float valor;
    }tabela[6] = {0};
    int idx;
    int tipo;
    float op1, op2;
    union tp_dado dado;

    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] >= 'A' && expr[i] <= 'F') {
            idx = expr[i] - 'A';
            if (tabela[idx].flag == 0) {
                printf("Digite o valor para %c: ", expr[i]);
                scanf("%f", &tabela[idx].valor);
                tabela[idx].flag = 1;
            }
            dado.num = tabela[idx].valor;
            push(p, 0, dado);
        }
        else {
            if (pilha_vazia(*p) == 1)
                return 1;
            pop(p, &tipo, &dado);
            op2 = dado.num;
            if (pilha_vazia(*p) == 1)
                return 2;
            pop(p, &tipo, &dado);
            op1 = dado.num;
            switch (expr[i]) {
                case '^':
                    dado.num = powf(op1, op2);
                    break;
                case '*':
                    dado.num = op1*op2;
                    break;
                case '/':
                    dado.num = op1/op2;
                    break;
                case '+':
                    dado.num = op1+op2;
                    break;
                case '-':
                    dado.num = op1-op2;
                    break;
                default:
                    return 4;
            }
            push(p, 0, dado);
        }
    }

    if (pilha_vazia(*p) == 1)
        return 1;
    pop(p, &tipo, &dado);
    if (pilha_vazia(*p) == 0)
        return 3;
    *resultado = dado.num;
    return 0;
}
