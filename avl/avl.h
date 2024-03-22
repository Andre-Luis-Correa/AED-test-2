//
// Created by andre on 22/03/2024.
//

#ifndef PROVA_AED_2_AVL_H
#define PROVA_AED_2_AVL_H

struct no {
    int info; // informação armazenada
    struct no * esq; // sub-árvore esquerda
    struct no * dir; // sub-árvore direita
    int fb; // fator de balanceamento
};
typedef struct no* arvoreAVL; //árvore é um ponteiro para um nó

arvoreAVL rotacaoEsquerda(arvoreAVL p) {
    arvoreAVL u = p->dir;
    arvoreAVL t2 = u->esq;
    u->esq = p;
    p->dir = t2;
    return u;
}

arvoreAVL rotacaoDireita(arvoreAVL p){
    arvoreAVL  u = p->esq;
    arvoreAVL t2 = u->dir;
    u->dir = p;
    p->esq = t2;
}

arvoreAVL rotacaoDireitaEsquerda(arvoreAVL p) {
    arvoreAVL u = p->dir;
    arvoreAVL v = u->esq;
    arvoreAVL t2 = v->esq;
    arvoreAVL t3 = v->dir;
    p->dir = t2;
    u->esq = t3;
    v->esq = p;
    v->dir = u;
    return v;
}

arvoreAVL rotacaoEsquerdaDireita(arvoreAVL p) {
    arvoreAVL u = p->esq;
    arvoreAVL v = u->dir;
    arvoreAVL t2 = v->esq;
    arvoreAVL t3 = v->dir;
    p->esq= t3;
    u->dir = t2;
    v->esq = u;
    v->dir = p;
    return v;
}

#endif //PROVA_AED_2_AVL_H
