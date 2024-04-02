//
// Created by andre on 22/03/2024.
//

#include <stdio.h>
#include "avl.h"

int main(){
    arvoreAVL r = NULL;

    insercao(&r, 9);
    insercao(&r, 3);
    insercao(&r, 27);
    insercao(&r, 11);
    insercao(&r, 31);
    insercao(&r, 32);
    insercao(&r, 40);
    printf("Soma = %d\n", soma(r));
    imprimir(r);
    printf("\n");
    printf("%d\n", remover(&r, 27));
    //remover(&r, 31);
    imprimir(r);

    return 0;
}