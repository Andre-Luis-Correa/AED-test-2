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

    imprimir_in_order(r);

    return 0;
}
