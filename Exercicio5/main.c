/*
        TAD Deque estático/sequencial de strings.
        Annelise Lima Carneiro, Leandro Barcelos Ferreira, Marcelo Prado e Marina Bagliano Silva.
        2022
*/

#include "deque.h"
#include <stdio.h>

#define MAX_CHAR 21

void imprime_deque(Deque d);
void limpa_entrada();

int main () {
    Deque d = NULL;
    int opcao = 0;
    int ret;
    char elem[MAX_CHAR];

    while (opcao != 9) {
        printf("-----TAD Deque estatico/sequencial de strings-----\n");
        printf("1 - Criar deque\n");
        printf("2 - Esvaziar deque\n");
        printf("3 - Apagar deque\n");
        printf("4 - Imprimir deque\n");
        printf("5 - Inserir elemento no final\n");
        printf("6 - Inserir elemento no inicio\n");
        printf("7 - Remover elemento do inicio\n");
        printf("8 - Remover elemento do final\n");
        printf("9 - Encerrar\n");
        printf("--------------------------------------------------\n");
        printf("Digite a opcao: ");

        ret = scanf("%d", &opcao);
        printf("\n");
        limpa_entrada();
        if (ret == 0)
            opcao = 0;

        switch (opcao) {
            case 1: {
                if (d != NULL)
                    printf("Erro: deque ja foi criado\n\n");
                else {
                    d = cria_deque();
                    if (d == NULL)
                        printf("Falha ao criar o deque\n\n");
                    else
                        printf("Deque criado com sucesso\n\n");
                }

                break;
            }
            
            case 2: {
                ret = esvazia_deque(d);
                if (ret == 0)
                    printf("Erro: deque ja vazio ou nao inicializado\n\n");
                else
                    printf("Deque esvaziado com sucesso\n\n");
                
                break;
            }

            case 3: {
                ret = apaga_deque(&d);
                if (ret == 0)
                    printf("Erro: deque nao inicializado\n\n");
                else
                    printf("Deque apagado com sucesso\n\n");
                
                break;
            }

            case 4: {
                imprime_deque(d);
                break;
            }


            case 5:
            case 6: {
                if (d == NULL) {
                    printf("Erro: deque nao inicializado\n\n");
                    break;
                }

                printf("Digite a string para insercao: ");
                ret = scanf("%[^\n]s", elem);
                limpa_entrada();
                if (ret == 0) {
                    printf("Erro ao ler a string\n\n");
                    break;
                }
                
                if (opcao == 5)
                    ret = insere_final(d, elem);
                else
                    ret = insere_inicio(d, elem);
                
                if (ret == 0)
                    printf("Erro: verifique se o deque nao esta cheio\n\n");
                else
                    printf("Elemento inserido com sucesso\n\n");
                
                break;
            }

            case 7:
            case 8: {
                if (d == NULL) {
                    printf("Erro: deque nao inicializado\n\n");
                    break;
                }
                
                if (opcao == 7) 
                    ret = remove_inicio(d, elem);
                else
                    ret = remove_final(d, elem);

                if (ret == 0)
                    printf("Erro: verifique se o deque nao esta vazio\n\n");
                else
                    printf("Elemento \"%s\" removido com sucesso\n\n", elem);
                
                break;
            }

            case 9: {
                printf("Programa encerrado\n");
                break;
            }

            default: {
                printf("Opcao invalida\n\n");
            }
        }
    }

    return 0;
}

void imprime_deque(Deque d) {
    char elem[MAX_CHAR];
    int n = tamanho_deque(d);
    
    if (n == -1) {
        printf("Erro: deque nao inicializado\n\n");
        return;
    }
    if (n == 0) {
        printf("Deque vazio\n\n");
        return;
    }

    printf("Deque (%d elementos): [\n", n);
    for(int i = 0; i < n; i++) {
        remove_inicio(d, elem);
        printf("  %s,\n", elem);
        insere_final(d, elem);
    }
    printf("]\n\n");
}

void limpa_entrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
