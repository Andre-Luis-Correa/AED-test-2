//
// Created by andre on 22/03/2024.
//

#include <stdio.h>
#include "avl.h"

int main(){
    arvoreAVL r = NULL;

    int retornoInsercao = insercao(&r, 10);
    retornoInsercao = insercao(&r, 1);
    retornoInsercao = insercao(&r, 2);
    retornoInsercao = insercao(&r, 11);
    retornoInsercao = insercao(&r, 45);
    retornoInsercao = insercao(&r, 14);
    retornoInsercao = insercao(&r, 6);
    retornoInsercao = insercao(&r, 3);
    retornoInsercao = insercao(&r, 50);
    retornoInsercao = insercao(&r, 13);

    imprimir(r);

    return 0;
}