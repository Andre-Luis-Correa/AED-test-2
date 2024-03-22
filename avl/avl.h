//
// Created by andre on 22/03/2024.
//

#ifndef PROVA_AED_2_AVL_H
#define PROVA_AED_2_AVL_H

#include <stdio.h>
#include <stdlib.h>

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
    p->esq = t3;
    u->dir = t2;
    v->esq = u;
    v->dir = p;
    return v;
}

int vazia(arvoreAVL * r){
    return (*r) == NULL;
}

// Insere uma chave na árvore AVL
// Entrada: raiz da árvore AVL e valor da chave
// Retorno: 1 se altura da árvore aumentou, 0 caso contrário
int insercao(arvoreAVL *r, int x) {
    // Caso 1: árvore vazia
    if (vazia(*r)) {
        // Aloca memória para o novo nó
        *r = (arvoreAVL) malloc(sizeof(struct no));
        // Define o valor da chave
        (*r)->info = x;
        // Inicializa os ponteiros para as subárvores como nulo
        (*r)->esq = (*r)->dir = NULL;
        // O fator de balanceamento (fb) é zero para um nó folha
        (*r)->fb = 0;
        // A altura da árvore aumentou, então retorna 1
        return 1;
    }
    // Árvore não vazia
    if (x < (*r)->info) { // Inserir na árvore esquerda
        // Chama recursivamente a função para inserir na subárvore esquerda
        if (insercao(&((*r)->esq), x)) {
            // Verifica o fator de balanceamento do nó pai após a inserção
            switch ((*r)->fb) {
                case -1:
                    (*r)->fb = 0; // Nó estava desbalanceado para a esquerda, agora está balanceado
                    return 0;
                case 0:
                    (*r)->fb = 1; // Nó estava balanceado, agora está desbalanceado para a esquerda
                    return 1; // A altura da árvore aumentou
                case 1: // Nó estava desbalanceado para a direita, rebalanceamento é necessário
                    if ((*r)->esq->fb >= 0) { // Rotação simples à direita
                        *r = rotacaoDireita(*r);
                        (*r)->dir->fb = 0;
                    } else { // Rotação dupla: esquerda e depois direita
                        *r = rotacaoEsquerdaDireita(*r);
                        switch ((*r)->fb) {
                            case -1:
                                (*r)->esq->fb = 1;
                                (*r)->dir->fb = 0;
                                break;
                            case 0:
                                (*r)->esq->fb = 0;
                                (*r)->dir->fb = 0;
                                break;
                            case 1:
                                (*r)->esq->fb = 0;
                                (*r)->dir->fb = -1;
                                break;
                        }
                    }
                    (*r)->fb = 0; // Atualiza o fator de balanceamento da nova raiz
                    return 0;
            }
        }
    } else { // Inserir na árvore direita
        // Chama recursivamente a função para inserir na subárvore direita
        if (insercao(&((*r)->dir), x)) {
            // Verifica o fator de balanceamento do nó pai após a inserção
            switch ((*r)->fb) {
                case 1:
                    (*r)->fb = 0; // Nó estava desbalanceado para a direita, agora está balanceado
                    return 0;
                case 0:
                    (*r)->fb = -1; // Nó estava balanceado, agora está desbalanceado para a direita
                    return 1; // A altura da árvore aumentou
                case -1: // Nó estava desbalanceado para a esquerda, rebalanceamento é necessário
                    if ((*r)->dir->fb <= 0) { // Rotação simples à esquerda
                        *r = rotacaoEsquerda(*r);
                        (*r)->esq->fb = 0;
                    } else { // Rotação dupla: direita e depois esquerda
                        *r = rotacaoDireitaEsquerda(*r);
                        switch ((*r)->fb) {
                            case -1:
                                (*r)->esq->fb = 1;
                                (*r)->dir->fb = 0;
                                break;
                            case 0:
                                (*r)->esq->fb = 0;
                                (*r)->dir->fb = 0;
                                break;
                            case 1:
                                (*r)->esq->fb = 0;
                                (*r)->dir->fb = -1;
                                break;
                        }
                    }
                    (*r)->fb = 0; // Atualiza o fator de balanceamento da nova raiz
                    return 0;
            }
        }
    }
}

#endif //PROVA_AED_2_AVL_H
