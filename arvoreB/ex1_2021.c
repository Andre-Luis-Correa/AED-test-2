//
// Created by andre on 21/03/2024.
//

#include <stdio.h>
#include <stdlib.h>

#define ORDEM 5
//Estrutura de nó para árvore B
//tom uma posição a mais de chave e ponteiro de filho para
//facilitar implementação da operação split
typedef struct no{
    int numChaves;
    int chave[ORDEM];
    struct no* filho[ORDEM+1];
} arvoreB;

int vazia(arvoreB* r){
    return r->numChaves == 0;
}

int overflow(arvoreB* r){
    r->numChaves == ORDEM;
}

// Função para contar o número total de chaves em uma árvore B
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
            return 1; // chave já está na árvore
        else if(info < r->chave[(*pos)])
            break; // info pode estar na sub-árvore filho[*pos]
    return 0; // chave n~ao est´a neste nó
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
    if(!buscaPos(r,info, &pos)){ // chave não está no nó r
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

void imprimir_arvore(arvoreB *r, int nivel) {
    if (r == NULL) // Caso base: se o nó for nulo, retorne
        return;

    int i;
    for (i = 0; i < r->numChaves; i++) {
        imprimir_arvore(r->filho[i], nivel + 1); // Imprima os filhos recursivamente
        printf("Chave %d\n", r->chave[i]); // Imprima a chave do nó
    }

    imprimir_arvore(r->filho[i], nivel + 1); // Imprima o último filho recursivamente
}

//pré-condição: k > 0
// Função para buscar a k-ésima chave em uma árvore B
int busca_k_esima(arvoreB* r, int k) {
    if (r == NULL || k <= 0) // Caso base: se o nó for nulo ou k for inválido, retorne -1
        return -1;

    // Variável para armazenar a contagem de chaves
    int contagem = k;

    // Percorre os filhos da árvore
    for (int i = 0; i <= r->numChaves; i++) {
        // Busca recursivamente nos filhos
        int chave = busca_k_esima(r->filho[i], contagem);
        // Se a chave foi encontrada em um dos filhos, retorne-a
        if (chave != -1)
            return chave;
    }

    // Se chegamos até aqui, significa que não encontramos a chave nos filhos
    // Portanto, verifique se a chave está neste nó
    for (int i = 0; i < r->numChaves; i++) {
        // Decrementa a contagem
        contagem--;
        // Se a contagem chegou a zero, encontramos a k-ésima chave
        if (contagem == 0)
            return r->chave[i];
    }

    // Se chegamos aqui, a k-ésima chave não foi encontrada nesta subárvore
    return -1;
}


void imprimir_primeiras_chaves(arvoreB *r, int *contagem) {
    if (r == NULL) // Caso base: se o nó for nulo ou já tivermos imprimido todas as chaves desejadas, retorne
        return;

    // Imprime as chaves dos filhos recursivamente
    for (int i = r->numChaves; i >= 0; i--) {
        imprimir_primeiras_chaves(r->filho[i], contagem);
    }

    // Imprime as chaves do nó atual
    for (int i = 0; i < r->numChaves && *contagem > 0; i++) {
        // Imprime a chave do nó atual
        (*contagem)--; // Decrementa o contador de chaves
        printf("Chave %d\n", r->chave[i]);

        // Se já imprimimos todas as chaves desejadas, pare
        if (*contagem <= 0)
            return;

    }
}





int main(){
    arvoreB * raiz = inicializa_arvore();

    raiz = insere(raiz, 50);
    raiz = insere(raiz, 10);
    raiz = insere(raiz, 15);
    raiz = insere(raiz, 20);
    raiz = insere(raiz, 70);
    raiz = insere(raiz, 80);
    raiz = insere(raiz, 6);
    raiz = insere(raiz, 8);
    raiz = insere(raiz, 11);
    raiz = insere(raiz, 12);
    raiz = insere(raiz, 16);
    raiz = insere(raiz, 18);
    raiz = insere(raiz, 21);
    raiz = insere(raiz, 25);
    raiz = insere(raiz, 27);
    raiz = insere(raiz, 29);
    raiz = insere(raiz, 54);
    raiz = insere(raiz, 56);
    raiz = insere(raiz, 71);
    raiz = insere(raiz, 76);
    raiz = insere(raiz, 81);
    raiz = insere(raiz, 89);

    printf("total chaves: %d\n", contarChaves(raiz));

    printf("Resultado = %d para k = %d \n", busca_k_esima(raiz, 1), 1);
    printf("Resultado = %d para k = %d \n", busca_k_esima(raiz, 6), 6);
    printf("Resultado = %d para k = %d \n", busca_k_esima(raiz, 22), 22);
    printf("Resultado = %d para k = %d \n", busca_k_esima(raiz, 23), 23);
    printf("Resultado = %d para k = %d \n", busca_k_esima(raiz, 50), 50);

    imprimir_arvore(raiz, 0);


    printf("\n\n");
    int contagem = 6;
    imprimir_primeiras_chaves(raiz, &contagem);

    //imprimir_arvore_posicao(raiz, 6);
    //imprimir_arvore_posicao(raiz, 22);

    limpar_arvore(raiz);

    return 0;
}