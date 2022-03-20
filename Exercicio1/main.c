#include <stdio.h>
#include "pilha.h"

int main()
{
    Pilha p = cria_pilha();
    char op;
    int num;
    int base;
    int x, resto;

    while(1){
    printf("----- Conversor de base numérica -----\n");
    printf("B - Decimal para Binário\n");
    printf("O - Decimal para Octal\n");
    printf("H - Decimal para Hexadecimal\n");
    printf("Digite uma opção: ");
    scanf(" %c", &op);
    printf("Digite o numero a ser convertido:");
    scanf("%d", &num);

    if (num < 0){
          printf("Voce digitou um numero negativo! Fim de programa! \n");
          return 0;
    }

    if (op == 'b' || op == 'B') {
        base = 2;
    }
    else if (op == 'o' || op == 'O') {
        base = 8;
    }
    else if (op == 'h' || op == 'H') {
        base = 16;
    }
    else{
        printf("Essa opção nao existe! Tente novamente!\n\n");
        continue;
    }

    if(num == 0){
       printf("0\n\n");
       continue;
    }
    
    esvazia_pilha(p);

    while(num !=0){
      resto = num%base;
      push(p, resto);
      num = num/base;
    }

    printf("O numero convertido eh: ");
    while( tamanho_pilha(p)!= 0){
        pop(p, &x);
        if (x < 10)
            printf("%d", x);
        else
            printf("%c", 'A'-10+x);
    }

    printf("\n\n");

    }
}
