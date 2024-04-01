//
// Created by andre on 21/03/2024.
//

#include <stdio.h>
#include "arvoreB.h"

//pré-condição: k > 0
// Função para buscar a k-ésima chave em uma árvore B
int busca_k_esima(arvoreB* r, int k) {
    if (r == NULL || k > contarChaves(r)) {
        return -1; // Árvore vazia ou valor de k inválido
    }

    if(r->filho[0] == NULL) { // Se for folha, retorna a chave na posição k
        if (k <= r->numChaves) {
            return r->chave[k - 1]; // A k-ésima chave está no nó atual
        }
    }else{
        for(int i = 0; i< r->numChaves; i++){
            printf("%d ", r->chave[i]);
            return busca_k_esima(r->filho[0], k-1);
        }
    }
}

// Function to perform selection in B-tree
// Function to perform selection in B-tree
int select(arvoreB* r, int k) {
    if (r == NULL || k > contarChaves(r))
        return -1; // Not found or empty node

    int sizeLeftSubtree = (r->filho[0] != NULL) ? r->filho[0]->numChaves : 0;
    printf("Tamanho da subtree esquerda = %d\n", sizeLeftSubtree);
    int i;

    // Find the appropriate child to visit
    for (i = 0; i < r->numChaves; i++) {
        if (k < sizeLeftSubtree) {
            return select(r->filho[i], k); // Retorna para o filho apropriado
        } else if (k == sizeLeftSubtree && i != r->numChaves) {
            return r->chave[i]; // k-ésimo elemento encontrado neste nó
        } else {
            k -= sizeLeftSubtree + 1; // Incrementa corretamente o tamanho da subárvore
        }
    }
}

int main(){
    arvoreB* raiz = (arvoreB*)malloc(sizeof(arvoreB));
    raiz->numChaves = 3;
    raiz->chave[0] = 15;
    raiz->chave[1] = 20;
    raiz->chave[2] = 25;

    arvoreB* b = (arvoreB*)malloc(sizeof(arvoreB));
    b->numChaves = 3;
    b->chave[0] = 12;
    b->chave[1] = 13;
    b->chave[2] = 14;
    b->filho[0] = NULL;
    b->filho[1] = NULL;
    b->filho[2] = NULL;
    b->filho[3] = NULL;

    arvoreB* c = (arvoreB*)malloc(sizeof(arvoreB));
    c->numChaves = 3;
    c->chave[0] = 16;
    c->chave[1] = 17;
    c->chave[2] = 18;
    c->filho[0] = NULL;
    c->filho[1] = NULL;
    c->filho[2] = NULL;
    c->filho[3] = NULL;

    arvoreB* d = (arvoreB*)malloc(sizeof(arvoreB));
    d->numChaves = 3;
    d->chave[0] = 21;
    d->chave[1] = 22;
    d->chave[2] = 23;
    d->filho[0] = NULL;
    d->filho[1] = NULL;
    d->filho[2] = NULL;
    d->filho[3] = NULL;

    arvoreB* e = (arvoreB*)malloc(sizeof(arvoreB));
    e->numChaves = 3;
    e->chave[0] = 26;
    e->chave[1] = 27;
    e->chave[2] = 28;
    e->filho[0] = NULL;
    e->filho[1] = NULL;
    e->filho[2] = NULL;
    e->filho[3] = NULL;

    raiz->filho[0] = b;
    raiz->filho[1] = c;
    raiz->filho[2] = d;
    raiz->filho[3] = e;
    imprimir_arvore(raiz);
    printf("Nos minimos: %d\n", conta_nos_minimo_chaves(raiz));
    printf("Valor maior na arvore: %d\n", proximaChave(raiz, 20));
    printf("Numero de nos: %d\n", contarNosArvoreB(raiz));
    printf("Numero de chaves: %d\n", contarChaves(raiz));
    printf("Busca k esima chave: %d\n", busca_k_esima(raiz, 1));
    printf("Busca k esima chave: %d\n", select(raiz, 10));
    limpar_arvore(raiz);
    return 0;
}
