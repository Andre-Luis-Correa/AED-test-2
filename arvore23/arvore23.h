//
// Created by andre on 22/03/2024.
//

#ifndef PROVA_AED_2_ARVORE23_H
#define PROVA_AED_2_ARVORE23_H

#include <stdio.h>
#include <stdlib.h>

struct no23 {
    int chave_esq; // chave esquerda
    int chave_dir; // chave direita
    struct no23 * esq; // sub-árvore esquerda
    struct no23 * meio; // sub-árvore do meio
    struct no23 * dir; // sub-árvore direita
    int n; // número de chaves no nó
};

typedef struct no23* arvore23; //árvore é um ponteiro para um nó

arvore23 criaNo23(int chave_esq, int chave_dir, arvore23 esq, arvore23 meio, arvore23 dir, int n){
    arvore23 novoNo = (struct no23*)malloc(sizeof(struct no23));
    novoNo->chave_esq = chave_esq;
    novoNo->chave_dir = chave_dir;
    novoNo->esq = esq;
    novoNo->meio = meio;
    novoNo->dir = dir;
    novoNo->n = n;
    return novoNo;
}

int vazia(arvore23 r){
    return r == NULL;
}

// Função para verificar se um nó é uma folha
int eh_folha(arvore23 r) {
    return r->esq == NULL;
}

// Retorno: ponteiro para o nó contendo a chave ou
// NULL caso a chave não pertença à árvore
arvore23 busca(arvore23 r, int chave){
    if(vazia(r))
        return NULL;
    if(r->chave_esq == chave)
        return r;
    if(r->n == 2 && r->chave_dir == chave)
        return r;
    if(chave < r->chave_esq)
        return busca(r->esq, chave);
    else if(r->n == 1 || chave < r->chave_dir)
        return busca(r->meio, chave);
    else
        return busca(r->dir, chave);
}

arvore23 split(arvore23 p, int chave, arvore23 subarvore, int *chave_promovida) {
    arvore23 paux;
    if (chave > p->chave_dir) { // chave ficará mais a direita
        *chave_promovida = p->chave_dir; // promove a antiga maior
        paux = p->dir;
        p->dir = NULL; // elimina o terceiro filho
        p->n = 1; // atualiza o número de chaves
        return criaNo23(chave, 0, paux, subarvore, NULL, 1);
    }
    if (chave >= p->chave_esq) { // chave está no meio
        *chave_promovida = chave; // continua sendo promovida
        paux = p->dir;
        p->dir = NULL;
        p->n = 1;
        return criaNo23(p->chave_dir, 0, subarvore, paux, NULL, 1);
    }
    // chave ficará mais à esquerda
    *chave_promovida = p->chave_esq;
    // primeiro cria o nó à direita
    paux = criaNo23(p->chave_dir, 0, p->meio, p->dir, NULL, 1);
    p->chave_esq = chave; // atualiza o nó À esquerda
    p->n = 1;
    p->dir = NULL;
    p->meio = subarvore;
    return paux;
}

// Adiciona uma chave em um nó que tem 1 chave
// Pré-condição: nó r tem somente uma chave
// Pós-condição: insere chave no nó r com sub-árvore p
void adicionaChave(arvore23 r, int chave, arvore23 p) {
    if(r->chave_esq < chave) {
        r->chave_dir = chave;
        r->dir = p;
    }
    else {
        r->chave_dir = r->chave_esq;
        r->chave_esq = chave;
        r->dir = r->meio;
        r->meio = p;
    }
    r->n = 2;
}

//Insere uma chave em uma árvore 2-3 retornando nó gerado pelo split e
// a chave a ser promovida
// Pré-condição: raiz não vazia
// Pós-condição: chave inserida em alguma sub-árvore de r
// Retorno: nó gerado no split e chave promovida ou NULL caso não tenha
// ocorrido split
arvore23 inserir_aux(arvore23 r, int chave, int *chave_promovida) {
    if (eh_folha(r)) { // caso base: está em uma folha
        if (r->n == 1) {
            adicionaChave(r, chave, NULL);
            return NULL;
        } else return split(r, chave, NULL, chave_promovida);
    } else { // precisa descer
        arvore23 paux;
        int ch_aux;
        if (chave < r->chave_esq)
            paux = inserir_aux(r->esq, chave, &ch_aux);
        else if ((r->n == 1) || (chave < r->chave_dir))
            paux = inserir_aux(r->meio, chave, &ch_aux);
        else
            paux = inserir_aux(r->dir, chave, &ch_aux);
        if (paux == NULL) // nao promoveu
            return NULL;
        if (r->n == 1) {
            adicionaChave(r, ch_aux, paux);
            return NULL;
        } else // precisa fazer split
            return split(r, ch_aux, paux, chave_promovida);
    }
}

// Insere a chave na árvore 2-3
arvore23 inserir(arvore23 r, int chave){
    if(vazia(r))  // caso base especial: a árvore é vazia
        return criaNo23(chave, 0, NULL, NULL, NULL, 1);

    int chave_promovida;
    arvore23 aux = inserir_aux(r, chave, &chave_promovida);
    if(!vazia(aux)) // cria nova raiz
        return criaNo23(chave_promovida, 0,r,aux,NULL,1);

    return r; // raiz não se altera
}

// Função para imprimir uma árvore 23 em ordem (in-order traversal)
void imprimir_in_order(arvore23 raiz) {
    if (!vazia(raiz)) {
        // Percorre a sub-árvore esquerda
        imprimir_in_order(raiz->esq);

        // Imprime a chave esquerda (se existir)
        printf("%d ", raiz->chave_esq);

        // Percorre a sub-árvore do meio (se existir)
        imprimir_in_order(raiz->meio);

        if(raiz->n == 2)
        // Imprime a chave direita (se existir)
        printf("%d ", raiz->chave_dir);

        // Percorre a sub-árvore direita
        imprimir_in_order(raiz->dir);
    }
}

int minimo(arvore23 r){
    if(!vazia(r->esq)){
        return minimo(r->esq);
    }
    return r->chave_esq;
}

int maximo(arvore23 r){
    if(!vazia(r->dir)){
        return maximo(r->dir);
    } else if(!vazia(r->meio)){
        return maximo(r->meio);
    } else if(!vazia(r->esq)){
        return maximo(r->esq);
    }
    return r->chave_dir;
}

int conta_nos(arvore23 r){
    if(!vazia(r)){
        return 1 + conta_nos(r->esq) + conta_nos(r->meio) + conta_nos(r->dir);
    }
    return 0;
}

int conta_chaves(arvore23 r){
    if(!vazia(r)){
        return r->n + conta_chaves(r->esq) + conta_chaves(r->meio) + conta_chaves(r->dir);
    }
    return 0;
}

void imprimir(arvore23 r){
    if( !vazia(r) ){
        imprimir(r->esq);
        printf("%d ", r->chave_esq);

        imprimir(r->meio);

        if(r->n == 2)
            printf("%d ", r->chave_dir);

        imprimir(r->dir);
    }
}

#endif //PROVA_AED_2_ARVORE23_H
