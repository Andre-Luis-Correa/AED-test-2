//
// Created by andre on 22/03/2024.
//

#ifndef PROVA_AED_2_ARVOREBMAIS_H
#define PROVA_AED_2_ARVOREBMAIS_H

#include <stdio.h>
#include <stdlib.h>

#define ORDEM 4 // Defina a ordem da árvore B+

typedef struct nodeBmais {
    int chave[ORDEM - 1];
    void* ponteiro[ORDEM];
    int eh_folha; // 1 = é folha, 0 = nó interno
    int numChaves;
} noBmais;

typedef noBmais* arvoreBMais;

void print_arvoreBMais(arvoreBMais raiz) {
    if (raiz != NULL) {
        int i;
        for (i = 0; i < raiz->numChaves; i++) {
            if (raiz->eh_folha == 0) {
                print_arvoreBMais((arvoreBMais)raiz->ponteiro[i]);
            }
            printf("%d ", raiz->chave[i]);
        }
        if (raiz->eh_folha == 0) {
            print_arvoreBMais((arvoreBMais)raiz->ponteiro[i]);
        }
    }
}

arvoreBMais buscarChave(arvoreBMais raiz, int chave, int *pos) {
    if (raiz == NULL) {
        printf("Árvore vazia.\n");
        return raiz;
    }

    arvoreBMais atual = raiz;

    // Percorre a árvore até chegar a uma folha
    while (!atual->eh_folha) {
        int i;
        // Encontra a posição do próximo nó filho a ser visitado
        for (i = 0; i < atual->numChaves; i++) {
            if (chave < atual->chave[i])
                break;
        }

        // Move para o próximo nó filho
        atual = (noBmais *) atual->ponteiro[i];
    }

    // Busca a chave na folha
    int i;
    for (i = 0; i < atual->numChaves; i++) {
        if (chave == atual->chave[i]) {
            // Atualiza o valor de pos com a posição da chave na folha
            if (pos != NULL)
                *pos = i;
            return atual; // Retorna o nó atual se a chave for encontrada
        }
    }

    // Se a chave não for encontrada na folha atual, realiza a busca recursivamente
    // no próximo nó interligado na folha
    return buscarChave((arvoreBMais)atual->ponteiro[ORDEM-1], chave, pos);
}

// Função para contar o número de folhas em uma árvore B+
// Conta o número de folhas em uma árvore B+ evitando percorrer nós desnecessários
int contarFolhas(arvoreBMais raiz) {
    if (raiz == NULL) {
        printf("Árvore vazia.\n");
        return 0;
    }

    int count = 0;
    noBmais *atual = raiz;

    // Percorre a árvore até chegar a uma folha
    while (!atual->eh_folha) {
        atual = (noBmais *) atual->ponteiro[0];
    }

    // Conta o número de folhas
    while (atual != NULL) {
        count++;
        atual = (noBmais *) atual->ponteiro[ORDEM-1]; // Avança para a próxima folha
    }
    return count;
}

#endif //PROVA_AED_2_ARVOREBMAIS_H
