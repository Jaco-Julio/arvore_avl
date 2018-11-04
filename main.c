/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: sbona
 *
 * Created on 18 de Outubro de 2018, 22:11
 */

#include <stdio.h>
#include <stdlib.h>
#include "TreeAVL.h"

int main(int argc, char** argv) {
    Tree*t = iniciaArvore();
    //printf("\nEndereço da raiz: %p", t);
    int TreeSize = 300;
    //srand(time(NULL));
    for (int i=0; i<TreeSize; i++){
        insereArvore(rand()%9999+1, t);
    }
//    insereArvore(5, t);
//    insereArvore(4, t);
//    insereArvore(2, t);
//    insereArvore(8, t);
//    insereArvore(6, t);
//    insereArvore(55, t);
//    

    printf("\nImprime em pré-ordem.\n");
    imprimePreOrdem(t);
    printf("\nImprime em ordem.\n");
    imprimeEmOrdem(t);
    printf("\nImprime em pós-ordem.\n");
    imprimePosOrdem(t);
    if(isEmpty(t)){
        printf("\nArvore vazia.");
    } else {
        printf("\nA altura da arvore é %d.", alturaArvore(t));
    }
    printf("\nA arvore possui %d nós.", totalNodesArvore(t));
    //printf("\nEm Ordem:");
    //imprimeEmOrdem(t);
    //printf("\nPreOrdem: ");
    //imprimePosOrdem(t);
    //printf("\nPosOrdem: ");
    //imprimePreOrdem(t);
    //printf("\nA árvore possue %d nós-folha.",contaNosFolha(t));
    //printf("\nA altura da árvore é %d.",alturaArvore(t));
    
    //menuRemove();
    
    return (EXIT_SUCCESS);
}
