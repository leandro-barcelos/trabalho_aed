#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

int main()
{
    char op;
    int num;
    int base;
    int x, resto;

    while(1){
    printf("-----Convertor de base numerica-----\n");
    printf("Para de um numero Decimal para Binario aperte (B) \n");
    printf("Para de um numero Decimal para Octal aperte (O) \n");
    printf("Para de um numero Decimal para Hexadecinal aperte (H) \n");
    printf("Digite uma opcao:");
    scanf(" %c", &op);
    printf("Digite o numero a ser convertido:");
    scanf("%d", &num);

    if(num < 0){
          printf("Voce digitou um numero negativo!Fim de programa! \n");
          return 0;
    }

    if(op == 'b' || op == 'B'){
        base = 2;
    }

    else if(op == 'o' || op == 'O'){
        base = 8;
    }
    else if(op == 'h' || op == 'H'){
        base = 16;
    }
    else{
        printf("Essa opcao nao existe! Tente novamente!\n\n");
        continue;
    }

    if(num == 0){
       printf("0\n\n");
       continue;
       }

    Pilha p = cria_pilha();


    while(num !=0){
      resto = num%base;
      push(p, resto);
      num = num/base;
    }

     printf("O numero convertido eh: ");
     while( tamanho_pilha(p)!= 0){
        pop(p, &x);
        printf("%d ", x);

    }

    printf("\n\n");
    }

    return 0;
}
