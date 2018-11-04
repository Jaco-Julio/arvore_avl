/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TreeAVL.c
 * Author: sbona
 * 
 * Created on 3 de Novembro de 2018, 17:00
 */
#include <stdio.h>
#include <stdlib.h>
#include "TreeAVL.h"

struct tree {
  int info; // chave
  int altura; // altura da árvore
  int fb; // fator de balanceamento
  struct tree *pai; // nó pai
  struct tree *esq; // nó a esquerda
  struct tree *dir; // nó a direita
  
};
Tree* iniciaArvore(){
    Tree* raiz = (Tree*) malloc(sizeof(Tree));
    if( raiz != NULL ){
        *raiz = NULL;
    }
    return raiz;
}
void liberaNodes(struct tree* node){
    if(node==NULL) return;
    liberaNodes(node->esq);
    liberaNodes(node->dir);
    free(node);
    node = NULL;
}
void liberaArvore(Tree* raiz){
    if(raiz==NULL) return;
    liberaNodes(*raiz);
    free(raiz);
}
int isEmpty(Tree* raiz){
    if(raiz==NULL) return 1;
    if(*raiz==NULL) return 1;
    return 0;
}
int max(int a, int b){
    if(a > b) {
        return a;
    } else {
        return b;
    }
}
int alturaArvore(Tree*raiz){
    if(raiz == NULL) return -1;
    if(*raiz == NULL) return 0;
    int altEsq = alturaArvore(&((*raiz)->esq));
    int altDir = alturaArvore(&((*raiz)->dir));
    int h = max(altEsq, altDir) + 1;
    (*raiz)->altura = h;
    (*raiz)->fb = altEsq- altDir;
    return h;
}
int totalNodesArvore(Tree*raiz){
    if(raiz == NULL) return -1;
    if(*raiz == NULL) return 0;
    int nodeEsq = alturaArvore(&((*raiz)->esq));
    int nodeDir = alturaArvore(&((*raiz)->dir));
    return (nodeEsq + nodeDir+1);
}
int hasChildren(Tree*raiz){
    if((*raiz)->esq == NULL || (*raiz)->dir == NULL ) return 0;
    return 1;
}
void imprimePreOrdem(Tree*raiz){
    if(raiz==NULL) printf("Deu ruim!");
    if(*raiz!=NULL) {
        //int h = alturaArvore(*raiz);
        alturaArvore(&(*raiz));
        int hasLeft = ((*raiz)->esq != NULL);
        int hasRight = ((*raiz)->dir != NULL);
        printf("{");
        printf("\n\t\"chave\":%d",(*raiz)->info);
        printf(",\n\t\"altura\":%d",(*raiz)->altura);
        printf(",\n\t\"balance\":%d",(*raiz)->fb);
        if(hasLeft || hasRight) printf(",\n\t\"children\":[");
            imprimePreOrdem(&((*raiz)->esq));
            if(hasLeft && hasRight) printf(",");
            imprimePreOrdem(&((*raiz)->dir));
        if(hasLeft || hasRight) printf("]");
        printf("\n}");
    } 
}
void imprimeEmOrdem(Tree*raiz){
    if(raiz==NULL) printf("Deu ruim!");
    if(*raiz!=NULL) {
        printf("(");
        imprimeEmOrdem(&((*raiz)->esq));
        printf("%d",(*raiz)->info);
        imprimeEmOrdem(&((*raiz)->dir));
        printf(")");
    } 
}
void imprimePosOrdem(Tree*raiz){
    if(raiz==NULL) printf("Deu ruim!");
    if(*raiz!=NULL) {
        printf("(");
        imprimePosOrdem(&((*raiz)->esq));
        imprimePosOrdem(&((*raiz)->dir));
        printf("%d",(*raiz)->info);
        printf(")");
    }
}
void rotacaoSimplesEsquerda(Tree*raiz){
    printf("\nrotação a direita.");
    struct tree *node = (*raiz)->dir;
    (*raiz)->dir = node->esq;
    node->esq = *raiz;
    *raiz = node;
}
void rotacaoSimplesDireita(Tree*raiz){
    printf("\nrotação a direita.");
    struct tree *node = (*raiz)->esq;
    (*raiz)->esq = node->dir;
    node->dir = *raiz;
    *raiz = node;
}
void rotacaoDuplaDireita(Tree*raiz){
    rotacaoSimplesEsquerda(&((*raiz)->esq));
    rotacaoSimplesDireita(&(*raiz));
}
void rotacaoDuplaEsquerda(Tree*raiz){
    rotacaoSimplesDireita(&((*raiz)->dir));
    rotacaoSimplesEsquerda(&(*raiz));
}

int insereArvore(int valor, Tree*raiz){
    if(raiz == NULL) return -1;
    if(*raiz == NULL) {
        struct tree *novo = (struct tree*) malloc(sizeof(struct tree));
        if(novo==NULL) printf("\nOpa! Não foi possível criar espaço na memória.");
        novo->info = valor;
        novo->altura = 0;
        novo->fb = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        //printf("\nInserindo %d", (*raiz)->info);
    } else {
        if((*raiz)->info == valor) {
            printf("\nO número %d já existe na árvore", valor);
        } else {
            if((*raiz)->info > valor){
                insereArvore(valor, &((*raiz)->esq));
            } else {
                insereArvore(valor, &((*raiz)->dir));
            }
            int h = alturaArvore(&(*raiz));
            if((*raiz)->fb>1){
                if((*raiz)->esq->info < valor){
                    printf("esquerda");
                    rotacaoDuplaDireita(&(*raiz));
                } else {
                    rotacaoSimplesDireita(&(*raiz));
                }
            }
            if((*raiz)->fb<-1){
                if((*raiz)->dir->info > valor){
                    printf("direita");

                   rotacaoDuplaEsquerda(&(*raiz));
                } else {
                   rotacaoSimplesEsquerda(&(*raiz));
                }
                //printf("*----> %d", (*raiz)->fb);
            }
            
            //if(*raiz->fb > 1)
            //rotacaoSimplesEsquerda(*raiz);
        }
    }
}