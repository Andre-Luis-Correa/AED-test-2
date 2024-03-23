//
// Created by andre on 22/03/2024.
//

#ifndef PROVA_AED_2_ARVOREBMAIS_H
#define PROVA_AED_2_ARVOREBMAIS_H

/* Tipo representado um nó na árvore B+, sendo genérico suficiente
* para representar tanto folhas quanto nós internos. A relação entre chaves
* e ponteiros difere em folhas e nós internos.
* Na folha, o índice da chave é igual ao índice do ponteiro de dados
* correspondente (de 0 a ordem -1). O último ponteiro aponta para a folha
* seguinte (à direita) ou NULL no caso de ser a folha mais à direita.
* Em um nó interno, o ponteiro i aponta para subárvore de nós com
* chaves menores que a chave i enquanto o ponteiro i+1 aponta para subárvore
* de nós com chaves maiores ou iguais à chave i.
*/
//typedef struct nodeBMais {
//    void **ponteiro; // vetor de ponteiros
//    int *chave; // vetor de chaves
//    struct nodeBMais *pai; // ponteiro para o nó-pai
//    int eh_folha; // booleano, verdadeiro quando nó é folha
//    int numChaves; // número de chaves no nó
//} noBMais;

#include <stdio.h>
#include <stdlib.h>

#define ORDEM 3 // Defina a ordem da árvore B+

typedef struct nodeBMais {
    void **ponteiro; // vetor de ponteiros
    int *chave; // vetor de chaves
    struct nodeBMais *pai; // ponteiro para o nó-pai
    int eh_folha; // booleano, verdadeiro quando nó é folha
    int numChaves; // número de chaves no nó
} noBMais;

#endif //PROVA_AED_2_ARVOREBMAIS_H
