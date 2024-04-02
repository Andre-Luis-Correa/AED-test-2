#include <stdio.h>
#include <stdlib.h>

#include "arvoreBMais.h"

int main() {
    arvoreBMais raiz = (arvoreBMais)malloc(sizeof(noBmais));
    raiz->numChaves = 3;
    raiz->eh_folha = 0;
    raiz->chave[0] = 15;
    raiz->chave[1] = 20;
    raiz->chave[2] = 25;

    arvoreBMais b = (arvoreBMais)malloc(sizeof(noBmais));
    b->numChaves = 3;
    b->eh_folha = 1;
    b->chave[0] = 12;
    b->chave[1] = 13;
    b->chave[2] = 14;
    b->ponteiro[0] = NULL;
    b->ponteiro[1] = NULL;
    b->ponteiro[2] = NULL;

    arvoreBMais c = (arvoreBMais)malloc(sizeof(noBmais));
    c->numChaves = 3;
    c->eh_folha = 1;
    c->chave[0] = 15;
    c->chave[1] = 17;
    c->chave[2] = 18;
    c->ponteiro[0] = NULL;
    c->ponteiro[1] = NULL;
    c->ponteiro[2] = NULL;
    b->ponteiro[3] = c;

    arvoreBMais d = (arvoreBMais)malloc(sizeof(noBmais));
    d->numChaves = 3;
    d->eh_folha = 1;
    d->chave[0] = 20;
    d->chave[1] = 22;
    d->chave[2] = 23;
    d->ponteiro[0] = NULL;
    d->ponteiro[1] = NULL;
    d->ponteiro[2] = NULL;
    c->ponteiro[3] = d;

    arvoreBMais e = (arvoreBMais)malloc(sizeof(noBmais));
    e->numChaves = 3;
    e->eh_folha = 1;
    e->chave[0] = 26;
    e->chave[1] = 27;
    e->chave[2] = 28;
    d->ponteiro[3] = e;
    e->ponteiro[0] = NULL;
    e->ponteiro[1] = NULL;
    e->ponteiro[2] = NULL;
    e->ponteiro[3] = NULL;

    raiz->ponteiro[0] = b;
    raiz->ponteiro[1] = c;
    raiz->ponteiro[2] = d;
    raiz->ponteiro[3] = e;

    print_arvoreBMais(raiz);
    printf("\nO numero de folhas e: %d\n\n", contarFolhas(raiz));
    int * pos = (int*) malloc(sizeof (int ));
    arvoreBMais a = NULL;
    a = buscarChave(raiz, 22, pos);
    printf("Teste 2\n");
    printf("%d < %d < %d : i = %d\n", a->chave[0], a->chave[1], a->chave[2], *pos);
    return 0;
}