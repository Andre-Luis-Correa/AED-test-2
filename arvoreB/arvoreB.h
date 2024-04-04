//
// Created by andre on 22/03/2024.
//

#ifndef PROVA_AED_2_ARVOREB_H
#define PROVA_AED_2_ARVOREB_H

#include <stdio.h>
#include <stdlib.h>

#define ORDEM 3
//Estrutura de nó para árvore B
//tom uma posição a mais de chave e ponteiro de filho para
//facilitar implementação da operação split
typedef struct no{
    int numChaves;
    int chave[ORDEM];
    struct no* filho[ORDEM+1];
} arvoreB;

int vazia(arvoreB* r){
    return r == NULL;
}

int overflow(arvoreB* r){
    r->numChaves == ORDEM;
}

// Função para contar o número total de chaves em uma árvore Bimpri
int contarChaves(arvoreB* raiz) {
    if (raiz == NULL)
        return 0;

    int totalChaves = raiz->numChaves; // Contabiliza as chaves no nó atual

    // Percorre os filhos do nó atual
    for (int i = 0; i <= raiz->numChaves; i++) {
        totalChaves += contarChaves(raiz->filho[i]);
    }

    return totalChaves;
}

int contarNosArvoreB(arvoreB* raiz) {
    if (raiz == NULL) {
        return 0; // Árvore vazia
    }

    int nos = 1; // Conta o próprio nó atual

    for (int i = 0; i <= raiz->numChaves; i++) {
        nos += contarNosArvoreB(raiz->filho[i]); // Recursão nos filhos
    }

    return nos;
}

//Quebra o nó x (com overflow) e retorna o nó criado e chave m que
// deve ser promovida
arvoreB* split(arvoreB* x, int * m) {
    arvoreB* y = (arvoreB*) malloc(sizeof(arvoreB));
    int q = x->numChaves/2;
    y->numChaves = x->numChaves - q - 1;
    x->numChaves = q;
    *m = x->chave[q]; // chave mediana
    int i = 0;
    y->filho[0] = x->filho[q+1];
    for(i = 0; i < y->numChaves; i++){
        y->chave[i] = x->chave[q+i+1];
        y->filho[i+1] = x->filho[q+i+2];
    }
    return y;
}

// busca a posição em que a chave info está ou estaria em um nó
// retorna 1 se a chave está presente ou 0 caso contrário
int buscaPos(arvoreB* r, int info, int * pos) {
    for((*pos)=0; (*pos) < r->numChaves; (*pos)++)
        if(info == r->chave[(*pos)])
            return 1; // chave j´a est´a na ´arvore
        else if(info < r->chave[(*pos)])
            break; // info pode estar na sub´arvore filho[*pos]
    return 0; // chave n~ao est´a neste n´o
}

int eh_folha(arvoreB* r) {
    return (r->filho[0] == NULL);
}

void adicionaDireita(arvoreB* r, int pos, int k, arvoreB* p){
    int i;
    for(i=r->numChaves; i>pos; i--){
        r->chave[i] = r->chave[i-1];
        r->filho[i+1] = r->filho[i];
    }
    r->chave[pos] = k;
    r->filho[pos+1] = p;
    r->numChaves++;
}

void insere_aux(arvoreB* r, int info){
    int pos;
    if(!buscaPos(r,info, &pos)){ // chave n~ao est´a no n´o r
        if(eh_folha(r)) {
            adicionaDireita(r,pos,info,NULL);
        }
        else {
            insere_aux(r->filho[pos],info);
            if(overflow(r->filho[pos])){
                int m; // valor da chave mediana
                arvoreB* aux = split(r->filho[pos],&m);
                adicionaDireita(r,pos,m,aux);
            }
        }
    }
}

// Insere uma chave na ´arvore B e retorna raiz modificada
arvoreB* insere(arvoreB * r, int info){
    if(vazia(r)) {
        r = (arvoreB *) malloc(sizeof( arvoreB));
        r->chave[0] = info;
        for(int i = 0; i < ORDEM; i++)
            r->filho[i] = NULL;
        r->numChaves = 1;
    }
    else {
        insere_aux(r, info);
        if (overflow(r)) { // verifica se precisa split
            int m;
            arvoreB * x = split(r, &m);
            arvoreB * novaRaiz = (arvoreB *) malloc(sizeof(arvoreB));
            novaRaiz->chave[0] = m;
            novaRaiz->filho[0] = r;
            novaRaiz->filho[1] = x;
            for (int i = (((int) ORDEM / 2) + 1); i < ORDEM; i++)
                r->filho[i] = NULL;
            novaRaiz->numChaves = 1;
            return novaRaiz;
        }
    }
}

arvoreB * inicializa_arvore(){
    arvoreB  * r = (arvoreB*) malloc(sizeof (arvoreB));
    for(int i = 0; i < ORDEM; i++)
        r->filho[i] = NULL;
    r->numChaves = 0;
    return r;
}

void limpar_arvore(arvoreB *r) {
    if (r == NULL) // Caso base: se o nó for nulo, retorne
        return;

    for (int i = 0; i <= r->numChaves; i++) {
        limpar_arvore(r->filho[i]); // Limpe os filhos recursivamente
    }

    free(r); // Libere o nó atual
}

void imprimir_arvore(arvoreB *r) {
    if (r == NULL) // Caso base: se o nó for nulo, retorne
        return;

    int i;
    for (i = 0; i <= r->numChaves; i++) {
        imprimir_arvore(r->filho[i]); // Imprima os filhos recursivamente
        if(i != r->numChaves)
            printf("Chave %d\n", r->chave[i]); // Imprima a chave do nó
    }

   // imprimir_arvore(r->filho[i]); // Imprima o último filho recursivamente
}

void redistribuirChaves(arvoreB* pai, int pos_filho_esq) {
    arvoreB* filho_esq = pai->filho[pos_filho_esq];
    arvoreB* filho_dir = pai->filho[pos_filho_esq + 1];

    // Caso em que o filho da esquerda tem chaves a menos
    if (filho_esq->numChaves < (ORDEM/2)) {
        // Mover a chave do pai para o filho da esquerda
        filho_esq->chave[filho_esq->numChaves] = pai->chave[pos_filho_esq];
        filho_esq->numChaves++;

        // Mover a primeira chave do filho da direita para o pai
        pai->chave[pos_filho_esq] = filho_dir->chave[0];

        // Mover o primeiro filho do filho da direita para o filho da esquerda
        filho_esq->filho[filho_esq->numChaves] = filho_dir->filho[0];

        // Reposicionar as chaves no filho da direita
        for (int i = 0; i < filho_dir->numChaves - 1; i++) {
            filho_dir->chave[i] = filho_dir->chave[i + 1];
            filho_dir->filho[i] = filho_dir->filho[i + 1];
        }
        // Mover o último filho do filho da direita para a posição correta
        filho_dir->filho[filho_dir->numChaves - 1] = filho_dir->filho[filho_dir->numChaves];

        // Atualizar o número de chaves no filho da direita
        filho_dir->numChaves--;
    }
        // Caso em que o filho da direita tem chaves a menos
    else {
        // Mover os filhos do filho da direita para frente
        for (int i = filho_dir->numChaves; i > 0; i--) {
            filho_dir->chave[i] = filho_dir->chave[i - 1];
            filho_dir->filho[i + 1] = filho_dir->filho[i];
        }
        filho_dir->filho[1] = filho_dir->filho[0];

        // Mover a chave do pai para o filho da direita
        filho_dir->chave[0] = pai->chave[pos_filho_esq];
        filho_dir->numChaves++;

        // Mover o último filho do filho da esquerda para a primeira posição do filho da direita
        filho_dir->filho[0] = filho_esq->filho[filho_esq->numChaves];

        // Mover a última chave do filho da esquerda para o pai
        pai->chave[pos_filho_esq] = filho_esq->chave[filho_esq->numChaves - 1];

        // Atualizar o número de chaves no filho da esquerda
        filho_esq->numChaves--;
    }
}

int proximaChave(arvoreB* r, int val) {
    if (r != NULL) {
        int i;
        if (r->filho[0] == NULL) {
            for (i = 0; i < r->numChaves; i++) {
                if (r->chave[i] > val) return r->chave[i];
            }
            return -1;
        }

        for (i = 0; i < r->numChaves; i++) {
            if (r->chave[i] > val){
                if(r->filho[i] == NULL) return r->chave[i];
                return proximaChave(r->filho[i], val);
            }
        }

        return proximaChave(r->filho[i], val);
    }

    return -1;
}

int conta_nos_minimo_chaves(arvoreB* r) {
    if (r == NULL) {
        return 0;
    }

    int count = 0;

    // Verificar se o nó atual tem o número mínimo de chaves
    if ( (r->filho[0] != NULL) && (r->numChaves == (ORDEM/2 + ORDEM%2) - 1) ) {
        count = 1;
    }

    // Percorrer recursivamente os filhos do nó atual
    for (int i = 0; i <= r->numChaves; i++) {
        count += conta_nos_minimo_chaves(r->filho[i]);
    }

    return count;
}

void printar_nivel(arvoreB* raiz, int nivel) {
    if (raiz == NULL)
        return;
    if (nivel == 1) {
        printf("[");
        for (int i = 0; i < raiz->numChaves; i++)
            printf("i:%d=(%d) ", i, raiz->chave[i]);
        printf("] ");
    }
    else if (nivel > 1) {
        for (int i = 0; i < raiz->numChaves + 1; i++)
            printar_nivel(raiz->filho[i], nivel - 1);
    }
}

int altura(arvoreB* raiz) {
    if (raiz == NULL)
        return 0;
    else {
        int altura_max = 0;
        for (int i = 0; i < raiz->numChaves + 1; i++) {
            int altura_filho = altura(raiz->filho[i]);
            if (altura_filho > altura_max)
                altura_max = altura_filho;
        }
        return altura_max + 1;
    }
}

void printar_arvoreB_por_nivel(arvoreB* raiz) {
    int h = altura(raiz);
    for (int i = 1; i <= h; i++) {
        printf("Nivel %d: ", i);
        printar_nivel(raiz, i);
        printf("\n");
    }
}

int soma(arvoreB* r) {
    if (vazia(r)) {
        return 0;
    }

    int sum = 0;

    // Soma as chaves válidas no nó atual
    for (int i = 0; i < r->numChaves; i++) {
        sum += r->chave[i];
    }

    // Percorre os filhos apenas se necessário
    for (int i = 0; i <= r->numChaves; i++) {
        sum += soma(r->filho[i]);
    }

    return sum;
}

void imprimir_chaves_no(arvoreB* r, int a, int b) {
    if (r == NULL) {
        return;
    }

    if (r->chave[0] > b) {
        imprimir_chaves_no(r->filho[0], a, b);
    } else if (r->chave[r->numChaves - 1] < a) {
        imprimir_chaves_no(r->filho[r->numChaves], a, b);
    }else{
        // Verifica se o intervalo [a, b] intersecta com o intervalo do nó atual
        for (int i = 0; i < r->numChaves; i++) {
            imprimir_chaves_no(r->filho[i], a, b);
            if (r->chave[i] > a && r->chave[i] < b) {
                printf("%d ", r->chave[i]);
            }
        }
    }
    // Último filho
    imprimir_chaves_no(r->filho[r->numChaves], a, b);
}


void concat_nodes(int index, arvoreB * r){
    if(r == NULL){
        return;
    }

    arvoreB * left_child = r->filho[index];
    arvoreB * right_child = r->filho[1];

    left_child->chave[left_child->numChaves] = r->chave[index];

    for(int i = 0; i < right_child->numChaves; i++){
        left_child->chave[left_child->numChaves + i + 1] = right_child->chave[i];
        left_child->filho[left_child->numChaves + i + 1] = right_child->filho[i];
    }

    left_child->filho[left_child->numChaves + right_child->numChaves + 1] = right_child->filho[right_child->numChaves];

    left_child->numChaves += right_child->numChaves + 1;

    for(int i = index + 1; i < r->numChaves; i++){
        r->chave[i - 1] = r->chave[i];
        r->filho[i - 1] = r->filho[i + 1];
    }

    r->numChaves--;

    free(right_child);

}

// void imprimirMaiores(arvoreB r, int k); // imprimir maior que k evitando nós desnecessáriosis
// Função para imprimir chaves maiores que k
void imprimirMaiores(arvoreB* raiz, int k) {
    if (raiz == NULL) {
        return;
    }

    for (int i = 0; i < raiz->numChaves; i++) {
        if (raiz->chave[i] > k) {
            imprimirMaiores(raiz->filho[i], k);
            printf("%d ", raiz->chave[i]);
        }
    }

    imprimirMaiores(raiz->filho[raiz->numChaves], k);
}


#endif //PROVA_AED_2_ARVOREB_H
