//
// Created by andre on 22/03/2024.
//

#include <stdio.h>
#include "arvore23.h"

int main(){
    arvore23 r = NULL;

    r = inserir(r, 60);
    r = inserir(r, 20);
    r = inserir(r, 10);
    r = inserir(r, 30);
    r = inserir(r, 25);
    r = inserir(r, 50);
    r = inserir(r, 5);
    r = inserir(r, 90);

    imprimir_in_order(r);
    printf("\n");
    imprimir_intervalo(r, 20, 30);
    printf("Soma: %d\n", soma(r));
    printf("Altura: %d\n", altura(r));
    printf("\nEssa e a chave minima na arvore 2-3: %d\n", minimo(r));
    printf("\nEssa e a chave maxima na arvore 2-3: %d\n", maximo(r));
    printf("\nEsse e o numero total de chaves na arvore 2-3: %d\n", conta_chaves(r));
    printf("\nEsse e o numero total de nos na arvore 2-3: %d\n", conta_nos(r));
    imprimir(r);
    return 0;
}
