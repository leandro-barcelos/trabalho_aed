/*
        TAD Lista Fila de Prioridade, dinâmica, encadeamento circular simples de pacientes.
        Annelise Lima Carneiro, Leandro Barcelos Ferreira, Marcelo Prado e Marina Bagliano Silva.
        2022
*/

#include "fpa.h"
#include <stdio.h>
#include <string.h>

Paciente pr;
void imprimir_fila(Fila f);

int main(){

    Fila f;
    int trem = 0;
    char escolha;
    int idade;
    char nome[10];
    char doenca, gravidade;
    float altura, peso;

    while(trem != 1){

        printf("--- TAD Lista Fila dinamica encadeada circular de paciente ---\n");
        printf("--Fila--\n");
        printf("\n[1] Criar Fila\n");
        printf("[2] Inserir paciente na Fila\n");
        printf("[3] Remover paciente da Fila\n");
        printf("[4] Esvaziar a Fila\n");
        printf("[5] Apagar Fila\n");
        printf("[6] Tamanho\n");
        printf("[7] Imprimir Fila \n");
        printf("[8] Sair\n");
        printf("--------------------------------------------\n");
        printf("Digite o valor desejado: ");

        scanf(" %c", &escolha);
        switch(escolha){
            case '1':
                f = cria_fila();
                    printf("A fila foi criada\n\n");
                break;

            case '2':
                printf("Digite o nome a ser inserido: ");
                scanf(" %s", nome);
                strcpy(pr.nome, nome);

                printf("Digite a idade a ser inserida: ");
                scanf("%d", &idade);
                pr.idade = idade;

                printf("Digite o peso a ser inserido: ");
                scanf(" %f", &peso);
                pr.peso = peso;

                printf("Digite a altura a ser inserida: ");
                scanf(" %f", &altura);
                pr.altura = altura;

                printf("Os doencas possiveis a serem inseridas sao: ");
                printf("\nC - cardiaca, N - neurologica, S - sanguinea ou R – respiratoria\n");
                printf("Digite a doenca a ser inserida (entre as opçoes acima): ");
                scanf(" %c", &doenca);
                pr.doenca = doenca;

                printf("Os possivel grau de gravidade a ser inserido varia de 1 a 5, sendo 1 a mais simples e 5 a mais grave\n");
                printf("Diante disso, digite o grau de gravidade a ser inserido: ");
                scanf(" %c", &gravidade);
                pr.gravidade = gravidade;


                if(insere(&f, pr) == 1)
                    printf("O paciente foi inserido com sucesso!.\n\n");
                else
                    printf("O paciente não foi adicionado.\n\n");
                break;

            case '3':
                if(remove_ini(&f, &pr) == 0)
                    printf("O paciente não foi encontrado...\n");
                else
                    printf("O paciente foi removido com sucesso!.\n");
                break;
            case '4':
//                if(esvazia_fila(&f) == 0)
//                    printf("A fila não pode ser esvaziada.\n");
//                else
//                    printf("A fila foi esvaziada com sucesso!.\n");

                break;

            case '5':
                apaga_fila(&f);
                printf("A fila foi apagada com sucesso!\n");
                break;

            case '6':
                if (tamanho_fila(f) >= 0)
                    printf("A fila tem tamanho igual a %d\n", tamanho_fila(f));
                else
                    printf("A fila é invalida...\n");

                break;

            case '7':
                if(f != NULL)
                   imprimir_fila(f);
              break;

            case '8':
                trem = 1;
                break;


            default:
                printf("Opcao invalida!\n");
            }
    }

    return 0;
}

void imprimir_fila(Fila f){

    if (fila_vazia(f)|| f == NULL)
            printf("Fila invalida ou vazia\n");
    else
    {
        Fila f2 = cria_fila();
        printf("A fila possui os pacientes:\n");
        while(!fila_vazia(f))
        {
            remove_ini(&f, &pr);
            insere(&f2, pr);
            printf("%s, %d - %c \n", pr.nome, pr.idade, pr.doenca);
        }
        while(!fila_vazia(f2))
        {
            remove_ini(&f2, &pr);
            insere(&f, pr);
        }
    }
}
