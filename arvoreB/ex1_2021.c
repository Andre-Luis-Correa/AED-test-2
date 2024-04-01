//
// Created by andre on 21/03/2024.
//

#include <stdio.h>
#include "arvoreB.h"

// Função para retornar o valor do último elemento até o fim da contagem
int ultimo_elemento_contagem(arvoreB *r, int *contagem) {
    if (vazia(r) || *contagem <= 0) // Caso base: se o nó for nulo ou já tivermos retornado todas as chaves desejadas, retorne
        return -1;

    // Variável para armazenar o último elemento encontrado
    int ultimo_elemento = -1;

    // Percorre os filhos da árvore recursivamente
    for (int i = r->numChaves; i >= 0; i--) {
        // Busca recursivamente nos filhos
        int chave = ultimo_elemento_contagem(r->filho[i], contagem);
        // Se a chave foi encontrada em um dos filhos, atualize o último elemento
        if (chave != -1)
            ultimo_elemento = chave;
    }

    // Percorre as chaves do nó atual
    for (int i = 0; i < r->numChaves && *contagem > 0; i++) {
        // Atualiza o último elemento
        ultimo_elemento = r->chave[i];
        (*contagem)--; // Decrementa o contador de chaves

        // Se já retornamos todas as chaves desejadas, pare
        if (*contagem <= 0)
            return ultimo_elemento;
    }

    // Retorna o último elemento encontrado
    return ultimo_elemento;
}

//pré-condição: k > 0
// Função para buscar a k-ésima chave em uma árvore B
int busca_k_esima(arvoreB* r, int k) {
    if(r == NULL || k > contarChaves(r)) return -1;
    return ultimo_elemento_contagem(r, &k);
}

int main(){
//    arvoreB * raiz = inicializa_arvore();
//
//    raiz = insere(raiz, 50);
//    raiz = insere(raiz, 10);
//    raiz = insere(raiz, 15);
//    raiz = insere(raiz, 20);
//    raiz = insere(raiz, 70);
////    raiz = insere(raiz, 80);
////    raiz = insere(raiz, 6);
////    raiz = insere(raiz, 8);
////    raiz = insere(raiz, 11);
////    raiz = insere(raiz, 12);
////    raiz = insere(raiz, 16);
////    raiz = insere(raiz, 18);
////    raiz = insere(raiz, 21);
////    raiz = insere(raiz, 25);
////    raiz = insere(raiz, 27);
////    raiz = insere(raiz, 29);
////    raiz = insere(raiz, 54);
////    raiz = insere(raiz, 56);
////    raiz = insere(raiz, 71);
////    raiz = insere(raiz, 76);
////    raiz = insere(raiz, 81);
////    raiz = insere(raiz, 89);
//
//    printf("total chaves: %d\n", contarChaves(raiz));
//
//    printf("Resultado = %d para k = %d \n", busca_k_esima(raiz, 1), 1);
//    printf("Resultado = %d para k = %d \n", busca_k_esima(raiz, 4), 4);
//    printf("Resultado = %d para k = %d \n", busca_k_esima(raiz, 22), 22);
//    printf("Resultado = %d para k = %d \n", busca_k_esima(raiz, 23), 23);
//    printf("Resultado = %d para k = %d \n", busca_k_esima(raiz, 50), 50);
//
//    imprimir_arvore(raiz);
//    int k = 8;
//    printf("Ultimo elemento: %d\n", busca_k_esima(raiz, k));

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
    limpar_arvore(raiz);
    return 0;
}
