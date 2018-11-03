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

/*
 * 
 */
typedef struct tree {
  int info; // chave
  int altura; // altura da árvore
  int fb; // fator de balanceamento
  struct tree *pai; // nó pai
  struct tree *esq; // nó a esquerda
  struct tree *dir; // nó a direita
  
} Tree;
Tree *raiz = NULL;

void inserir(int valor, Tree*t);
void remover(int valor, Tree*t);
void iniciaArvore(int value);
void imprimeEmOrdem(Tree *t);
void imprimePreOrdem(Tree *t);
void imprimePosOrdem(Tree *t);
int isEmpty(Tree *t);
void menuAdiciona();
void menuRemove();
int contaNosFolha(Tree*t);
int max(int a,int b);
int alturaArvore(Tree*t);
void criaJson(Tree*t);
int maiorNo(Tree*t);

/*
 *
 */
int main(int argc, char** argv) {
    menuAdiciona();
    printf("\nEm Ordem: ");
    imprimeEmOrdem(raiz);
    printf("\nPreOrdem: ");
    imprimePosOrdem(raiz);
    printf("\nPosOrdem: ");
    imprimePreOrdem(raiz);
    printf("\nA árvore possue %d nós-folha.",contaNosFolha(raiz));
    printf("\nA altura da árvore é %d.",alturaArvore(raiz));
    printf("\nCria Json:");
    criaJson(raiz);
    
    menuRemove();
    
    return (EXIT_SUCCESS);
}

void menuAdiciona(){
  int total=0, count=0;
  printf("\nOuantos números quer adicionar?");
  scanf("%d",&total);
  while(count < total){
    int n = 0;
    printf("número %d: ",count+1);
    scanf("%d",&n);
    count++;
    inserir(n, raiz);
  }
}
void menuRemove(){
  int total=0, count=0;
  printf("\nQuantos números deseja remover?");
  scanf("%d",&total);
  while(count < total){
    int n = 0;
    printf("número %d: ",count+1);
    scanf("%d",&n);
    count++;
    remover(n, raiz);
  }
}
void iniciaArvore(int value){
    raiz = (Tree*) malloc(sizeof(Tree));
    raiz->info = value;
    raiz->esq = NULL;
    raiz->dir = NULL;
    raiz->pai = NULL;
}
int isEmpty(Tree *t){
  return t==NULL;
}
void imprimeEmOrdem(Tree *t){
  //printf("<--%d", t);
  if(!isEmpty(t)){
    printf("(");
    imprimeEmOrdem(t->esq);
    printf("%d",t->info);
    imprimeEmOrdem(t->dir);
    printf(")");
    
  }
}
void imprimePreOrdem(Tree *t){
    //printf("<--%d", t);
    if(!isEmpty(t)){
        printf("(");
        printf("%d",t->info);
        imprimePreOrdem(t->esq);
        imprimePreOrdem(t->dir);
        printf(")");
    }
}
void imprimePosOrdem(Tree *t){
    //printf("<--%d", t);
    if(!isEmpty(t)){
        printf("(");
        imprimePosOrdem(t->esq);
        imprimePosOrdem(t->dir);
        printf("%d",t->info);
        printf(")");

    }
}
void remover(int valor, Tree*t){
    // verifica se a árvore não está vazia (raiz != null)
    if(raiz != NULL) {
        // ponteiro auxiliar para correr os nós da árvore
        Tree*pai;
        //looping para percorrer a árvore
        //printf("\nTesta valor. %d\n", t->info);
        while(t != NULL && t->info != valor){
            pai = t; // auxiliar recebe o nó atual
              if(valor < pai->info) { // testa valor procurado
                  t = t->esq; // se for menor, procura no caminho da esquerda
              } else {
                  t = t->dir;// se for maior, procura no caminho da direita
              } 
          }
        // se não encontrar o valor, t será nulo.
        if(t!=NULL){ // valor encontrado
           printf("\n## Removendo %d da árvore. ##\n", valor);
           if(t->esq == NULL && t->dir==NULL){ // nó é folha
                if(pai->esq == t) {
                    //se o nó estiver a esquerda do pai
                    pai->esq = NULL;
                } else {
                    //se o nó estiver a direita do pai
                    pai->dir = NULL;
                }
                free(t); // libera memória
                printf("Esse era um nó folha.\n");
            }
            if(t->esq != NULL && t->dir==NULL){ // nó a ser removido só tem valores a esquerda
                  //t = NULL;
                if(pai->esq == t) { //se o nó removido estiver a esquerda do pai
                   pai->esq = t->esq; // o nó da esquerda do removido irá para esquerda do pai 
                } else { //se o nó removido estiver a direita do pai
                   pai->dir = t->esq; // o nó da esquerda do removido irá para direita do pai 
                }
                free(t);
                printf("Tinha nó a esquerda e não tinha nó a direita.\n");
            }
            if(t->esq == NULL && t->dir!=NULL){  // nó a ser removido só tem valores a direita
                if(pai->esq == t) { //se o nó removido estiver a esquerda do pai
                    pai->esq = t->dir; // o nó da direita do removido irá para esquerda do pai 
                } else { //se o nó removido estiver a direita do pai
                    pai->dir = t->dir; // o nó da direita do removido irá para direita do pai 
                }
                  free(t);
                printf("Tinha nó a direita e não tinha nó a esquerda.\n");
            }
            if(t->esq != NULL && t->dir!=NULL){ // nó a ser removido tem valores a direita e a esquerda
                //encontrar o maior mais próximo
                Tree*aux = t; // ponteiro auxiliar para armazenar posição do nó removido
                while( t->esq != NULL ){ // looping para encontrar o maior valor mais próximo
                    pai = t;
                    t = t->esq;
                }
                aux->info = t->info; // troca de valor com o valor encontrado
                //free(t); // libera memória
                pai->esq = NULL; // deleta o nó com o maior valor encontrado
                //printf("tem 2 filhos.\n");
                free(t);
            }
            imprimeEmOrdem(raiz);
            printf("\n");
        } else {
            printf("número não encontrado.\n");
        }
    } else {
        printf("A árvore está vazia.\n");
    }
}
void inserir(int valor, Tree*t){
    if(raiz == NULL){
        iniciaArvore(valor);
    } else {
        Tree*pai;
        while(t != NULL && t->info != valor){
            pai = t;
            if(valor < pai->info) t = t->esq;
            else t = t->dir;
        }
        t = (Tree*) malloc(sizeof(Tree));
        t->info = valor;
        t->esq = NULL;
        t->dir = NULL;
        if(valor < pai->info) pai->esq = t;
        else pai->dir = t;
    }
}
int contaNosFolha(Tree*t){
    if(t==NULL) return 0;
    if(t->esq==NULL && t->dir == NULL) return 1;
    int nosFolha = contaNosFolha(t->esq) + contaNosFolha(t->dir);
    return nosFolha;
}
int max(int a, int b){
    if(a>b){
        return a;
    }else{
        return b;
    }
}
int alturaArvore(Tree*t){
    if(t==NULL) return -1;
    int h_esq = alturaArvore(t->esq);
    int h_dir = alturaArvore(t->dir);
    t->altura = max(h_esq, h_dir)+1; 
    return t->altura;
}


void criaJson(Tree *t){
    //printf("<--%d", t);
    if(!isEmpty(t)){
        printf("{");
        printf("\n");
        if((t->esq == NULL)&&(t->dir == NULL)){
          printf("\"chave\":%d",t->info);
        }else{
          printf("\"chave\":%d,",t->info);
          printf("\n");
          if( (alturaArvore(t->dir)) ==(alturaArvore(t->esq))){
            printf("\"children\":[");
            criaJson(t->esq);
            printf(",");
            criaJson(t->dir);
            printf("]");
          }else{
            printf("\"children\":[");
            criaJson(t->esq);
            criaJson(t->dir);
            printf("]");
          } 
        }
        if((t->esq == NULL)&&(t->dir == NULL)){
          printf("}");
        }else{
          printf("},");
        }
        
    }
}
