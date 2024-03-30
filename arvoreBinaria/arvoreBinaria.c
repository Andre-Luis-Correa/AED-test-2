//
// Created by andre on 29/03/2024.
//

#include <stdio.h>
#include "arvoreBinaria.h"

int main()
{
    arvore a = NULL;

    a = inserir(a, 8);
    a = inserir(a, 4);
    a = inserir(a, 2);
    a = inserir(a, 6);
    a = inserir(a, 1);
    a = inserir(a, 3);
    a = inserir(a, 5);
    a = inserir(a, 7);
    a = inserir(a, 12);
    a = inserir(a, 10);
    a = inserir(a, 13);
    a = inserir(a, 9);
    a = inserir(a, 11);
    a = inserir(a, 14);
    //a = inserir(a, 15);

    printf("In ordem: "); inordem(a); printf("\n");
    printf("Pre ordem: "); preordem(a); printf("\n");
    printf("Pos ordem: "); posordem(a); printf("\n\n");

    printf("Altura: %d\n", altura(a));

    printf("E AVL tambem? %d", isAVL(a));

    return 0;
}