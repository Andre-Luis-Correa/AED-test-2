//
// Created by andre on 29/03/2024.
//

#ifndef PROVA_AED_2_ARVOREBINARIA_H
#define PROVA_AED_2_ARVOREBINARIA_H

#include <stdio.h>
#include <stdlib.h>

struct no { // estrutura de n´o para ´arvore bin´aria
    int info;
    struct no* esq;
    struct no* dir;
};

typedef struct no* arvore;

struct no_fila {
    arvore info;
    struct no_fila* prox;
};

typedef struct no_fila* fila;

// cria uma fila vazia
fila cria_fila() {
    return NULL;
}

// verifica se a fila está vazia
int vazia_fila(fila f) {
    return (f == NULL);
}

void libera_fila(fila f) {
    while (!vazia_fila(f)) { // enquanto a fila não estiver vazia
        fila aux = f->prox; // guarda o próximo nó da fila
        free(f); // libera a memória do nó atual
        f = aux; // avança para o próximo nó
    }
}

// insere um elemento na fila
fila insere_fila(fila f, arvore x) {
    fila novo = (struct no_fila*) malloc(sizeof(struct no_fila));
    novo->info = x;
    novo->prox = NULL;
    if (vazia_fila(f)) return novo;
    fila aux = f;
    while (aux->prox != NULL) aux = aux->prox;
    aux->prox = novo;
    return f;
}

// remove um elemento da fila
fila remove_fila(fila f, arvore* x) {
    if (vazia_fila(f)) return f;
    fila aux = f->prox;
    *x = f->info;
    free(f);
    return aux;
}

int vazia(arvore r){
    return (r == NULL);
}

// imprime as chaves por níveis
void imprimir_por_niveis(arvore r) {
    if(vazia(r)) return;
    fila f = cria_fila(); // cria uma fila vazia
    f = insere_fila(f, r); // insere a raiz na fila
    while (!vazia_fila(f)) { // enquanto a fila não estiver vazia
        int n = 0; // contador de nós no nível atual
        fila aux = f; // ponteiro auxiliar para percorrer a fila
        while (aux != NULL) { // conta quantos nós há na fila
            n++;
            aux = aux->prox;
        }
        while (n > 0) { // enquanto houver nós no nível atual
            arvore x; // variável para armazenar o nó removido da fila
            f = remove_fila(f, &x); // remove o primeiro nó da fila
            printf("%d ", x->info); // imprime a chave do nó
            if (x->esq != NULL) f = insere_fila(f, x->esq); // insere o filho esquerdo na fila, se existir
            if (x->dir != NULL) f = insere_fila(f, x->dir); // insere o filho direito na fila, se existir
            n--; // decrementa o contador de nós no nível atual
        }
        printf("\n"); // imprime uma quebra de linha após cada nível
    }
    libera_fila(f); // libera a memória da fila
}


arvore inserir(arvore r, int x){
    if(vazia(r)){
        r = (struct no*) malloc(sizeof(struct no));
        r->info = x;
        r->esq = NULL;
        r->dir = NULL;
    }

    else if(x < r->info)
        r->esq = inserir(r->esq, x);
    else
        r->dir = inserir(r->dir, x);

    return r;
}

void inordem(arvore r){
    if(!vazia(r)){
        inordem(r->esq);
        printf("%d ", r->info);
        inordem(r->dir);
    }
}

void preordem(arvore r){
    if(!vazia(r)){
        printf("%d ", r->info);
        preordem(r->esq);
        preordem(r->dir);
    }
}

void posordem(arvore r){
    if(!vazia(r)){
        posordem(r->esq);
        posordem(r->dir);
        printf("%d ", r->info);
    }
}

int maximo(arvore r){
    while(!vazia(r->dir)){
        r = r->dir;
    }

    return r->info;
}

int minimo(arvore r){
    while(!vazia(r->esq)){
        r = r->esq;
    }

    return r->info;
}

arvore remover(arvore r, int x){
    if(vazia(r))
        return NULL;
    else if(x < r->info)
        r->esq = remover(r->esq, x);
    else if(x > r->info)
        r->dir = remover(r->dir, x);
    else{ // A chave é igual o valor da raiz

        if(r->esq == NULL && r->dir == NULL){ // Nó a ser eliminado é o último (não há nem esq nem dir)
            free(r);
            return NULL;
        }

        if(r->esq == NULL){ // Só tem filho da direita
            r->info = minimo(r->dir);
            r->dir = remover(r->dir, r->info);
        }else{ // Só tem filho da esq ou dois filhos
            r->info = maximo(r->esq);
            r->esq = remover(r->esq, r->info);
        }
    }
    return r;
}


int altura(arvore r) {
    if (vazia(r)) return -1;
    else {
        int esq = altura(r->esq);
        int dir = altura(r->dir);
        if (esq > dir) return esq + 1;
        else return dir + 1;
    }
}

int isAVL(arvore r) {
    if (!vazia(r)) {
        int diferenca_altura = altura(r->esq) - altura(r->dir);
        if (diferenca_altura >= -1 && diferenca_altura <= 1) {
            // Verifica se as subárvores também são AVL
            if (!vazia(r->esq) && !isAVL(r->esq))
                return 0;
            if (!vazia(r->dir) && !isAVL(r->dir))
                return 0;
            return 1;
        } else {
            return 0;
        }
    }
    return 1; // Retorna 1 para árvore vazia ou nó folha
}


int soma(arvore r){
    if(vazia(r))
        return 0;

    return r->info + soma(r->esq) + soma(r->dir);
}


// Função que soma nós com valor dentro de um determinado intervalo aberto
int soma_intervalo(arvore r, int a, int b){
    if(vazia(r))
        return 0;

    if(r->info > a && r->info < b){ //Verifica se a chave está dentro do intervalo desejado
        int deve_somar_esq = 0; // Fazem o controle se o nó deve ser somado ou não
        int deve_somar_dir = 0;
        int deve_pular_esq = 0; // Fazem o controle caso o nó tenha que ser ser ignorado
        int deve_pular_dir = 0;

        //Verifica se há nó na esquerda
        if(!vazia(r->esq)){
            if((r->esq->info > a && r->esq->info < b)) // Caso o nó não esteja vazio e a chave esteja dentro do intervalo, então ele é considerado na soma
                deve_somar_esq = 1;
            else deve_pular_esq = -1; // Caso ele não esteja dentro do intervalo, ele pe ignorado da soma
        }

        if(!vazia(r->dir)){
            if(r->dir->info > a && r->dir->info < b) // Caso o nó não esteja vazio e a chave esteja dentro do intervalo, então ele é considerado na soma
                deve_somar_dir = 1;
            else deve_pular_dir = -1; // Caso ele não esteja dentro do intervalo, ele pe ignorado da soma
        }


        if((deve_somar_esq == 1 || deve_pular_esq == -1) && (deve_somar_dir == 1 || deve_pular_dir == -1)) // Faz a verificação se há esquerda e direita
            return r->info + soma_intervalo(r->esq, a, b) + soma_intervalo(r->dir, a, b);

        else if(deve_somar_esq == 1 || deve_pular_esq == -1) // Caso só tenha nó a esquerda
            return r->info + soma_intervalo(r->esq, a, b);

        else if(deve_somar_dir == 1 || deve_pular_dir == -1) // Caso só tenha  nó a direita
            return r->info+ soma_intervalo(r->dir, a, b);

        return r->info;
    }

    return soma_intervalo(r->esq, a, b) + soma_intervalo(r->dir, a, b); // Caso a chave não esteja no intervalo
}

int soma_nos_intervalo(arvore r, int a, int b) {
    if (r == NULL) {
        return 0;
    }

    // Verifica se o valor do nó está dentro do intervalo
    if (r->info >= a && r->info <= b) {
        // Soma os valores do nó e dos nós filhos recursivamente
        return r->info + soma_nos_intervalo(r->esq, a, b) + soma_nos_intervalo(r->dir, a, b);
    } else if (r->info < a) {
        // Se o valor do nó for menor que o limite inferior, busca apenas no lado direito
        return soma_nos_intervalo(r->dir, a, b);
    } else {
        // Se o valor do nó for maior que o limite superior, busca apenas no lado esquerdo
        return soma_nos_intervalo(r->esq, a, b);
    }
}

void print_intervalo(arvore r, int a, int b){
    if (!vazia(r)){
        if (r->info > b) print_intervalo(r->esq, a, b);

        if (r->info >= a && r->info <= b) {
            print_intervalo(r->esq, a, b);
            printf("%d ", r->info);
            print_intervalo(r->dir, a, b);
        }

        if (r->info < a) print_intervalo(r->dir, a, b);
    }
}

int chave_seguinte(arvore r, int x){
    if(vazia(r)) return -1;

    if(r->info == x){
        arvore aux = r->dir;
        if(vazia(aux)) return -1;
        while(!vazia(aux->esq)){
            aux = aux->esq;
        }
        return aux->info;
    }
    if(r->info > x){
        int res = chave_seguinte(r->esq, x);
        if (res == -1) return r->info;
        else return res;
    }
    if(r->info < x) return chave_seguinte(r->dir, x);
}


#endif //PROVA_AED_2_ARVOREBINARIA_H
