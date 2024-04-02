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
    return u;
}

arvoreAVL rotacaoDireitaEsquerda(arvoreAVL p) {
    p->dir = rotacaoDireita(p->dir); // Rotação à direita no filho direito
    return rotacaoEsquerda(p); // Rotação à esquerda no nó atual
}

arvoreAVL rotacaoEsquerdaDireita(arvoreAVL p) {
    p->esq = rotacaoEsquerda(p->esq); // Rotação à esquerda no filho esquerdo
    return rotacaoDireita(p); // Rotação à direita no nó atual
}

int vazia(arvoreAVL r){
    return (r == NULL);
}

int atualizar_fb_apos_insercao_esquerda(arvoreAVL *r) {
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

// Função auxiliar para atualizar o fator de balanceamento após a inserção
int atualizar_fb_apos_insercao_direita(arvoreAVL *r) {
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
            return atualizar_fb_apos_insercao_esquerda(r);
        }
    } else if (insercao(&((*r)->dir), x)) { // Inserir na árvore direita // Chama recursivamente a função para inserir na subárvore direita
       return atualizar_fb_apos_insercao_direita(r);
    }
}

int maximo(arvoreAVL r){
    while(!vazia(r->dir)){
        r = r->dir;
    }

    return r->info;
}

int minimo(arvoreAVL r){
    while(!vazia(r->esq)){
        r = r->esq;
    }

    return r->info;
}

// Função para remover uma chave da árvore AVL
// Entrada: raiz da árvore AVL e valor da chave a ser removida
// Retorno: 1 se a chave foi removida com sucesso, 0 caso contrário
int remover(arvoreAVL *r, int x) {
    if (vazia(*r))
        return 0;
    else if (x < (*r)->info) {
        if (remover(&((*r)->esq), x)) return atualizar_fb_apos_insercao_direita(r);
    }else if (x > (*r)->info) {
        if (remover(&((*r)->dir), x)) return atualizar_fb_apos_insercao_esquerda(r);
    }else { // A chave é igual ao valor da raiz

        if ((*r)->esq == NULL && (*r)->dir == NULL) { // Nó a ser eliminado é uma folha
            free(*r);
            *r = NULL;
            return 1;
        } else if ((*r)->esq == NULL) { // Só tem filho da direita
            arvoreAVL temp = *r;
            *r = (*r)->dir;
            free(temp);
            return 1;
        } else if ((*r)->dir == NULL) { // Só tem filho da esquerda
            arvoreAVL temp = *r;
            *r = (*r)->esq;
            free(temp);
            return 1;
        } else { // Tem ambos os filhos
            printf("AQUIII\n");
            // Encontra o sucessor na subárvore direita
            (*r)->info = minimo((*r)->dir);
            // Remove o sucessor encontrado da subárvore direita
            if (remover(&((*r)->dir), (*r)->info)) {
                // Atualiza o fator de balanceamento após a remoção na subárvore direita
                return atualizar_fb_apos_insercao_esquerda(r);
            }
        }
    }
    return 0; // Chave não encontrada
}

void imprimir(arvoreAVL r){
    if(!vazia(r)){
        imprimir(r->esq);
        printf("Chave: %d\n", r->info);
        imprimir(r->dir);
    }
}

int soma(arvoreAVL r){
    if(vazia(r)) return 0;
    return r->info + soma(r->esq) + soma(r->dir);
}

#endif //PROVA_AED_2_AVL_H