/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TreeAVL.h
 * Author: sbona
 *
 * Created on 3 de Novembro de 2018, 17:00
 */


typedef struct tree*Tree;

Tree* iniciaArvore();
void liberaArvore(Tree* raiz);
int isEmpty(Tree* raiz);
int alturaArvore(Tree*raiz);
int totalNodesArvore(Tree*raiz);
void imprimePreOrdem(Tree*raiz);
void imprimeEmOrdem(Tree*raiz);
void imprimePosOrdem(Tree*raiz);
void rotacaoSimplesEsquerda(Tree*raiz);
void rotacaoSimplesDireita(Tree*raiz);
void rotacaoDuplaEsquerda(Tree*raiz);
void rotacaoDuplaDireita(Tree*raiz);

int insereArvore(int valor, Tree*raiz);
