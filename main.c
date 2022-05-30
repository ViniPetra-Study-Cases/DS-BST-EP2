#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define MAX(a, b)   ((a > b) ? a : b)

//BST simples
typedef struct nodeBST{
  int info;
  int altura;
  struct nodeBST* esq;
  struct nodeBST* dir;
}nodeBST;
typedef nodeBST* BST;

BST bstNewNode(int value){
  BST node = malloc(sizeof(nodeBST));
  node->dir = NULL;
  node->esq = NULL;
  node->info = value;
  node->altura = 1;
  return node;
}

BST bstSearch(BST root, int target){
  if(root == NULL || root->info == target){
      return root;
  }
  else if(root->info > target){
      return bstSearch(root->esq, target);
  }
  else
  {
      return bstSearch(root->dir, target);
  }
}

BST bstInsert(BST root, int value){
  if(root == NULL){
      return bstNewNode(value);
    }

    if(root->info == value){
      return root;
    }

    if(root->info > value){
      root->esq = bstInsert(root->esq, value);
    }

    else {
      root->dir = bstInsert(root->dir, value);
  }

  return root;
}

int bstHeight(BST root){
  if(root == NULL) {
    return -1;
  }
  else
  {
    int esq = bstHeight(root->esq);
    int dir = bstHeight(root->dir);

    if(esq > dir){
      return esq + 1;
    }
    else
    {
      return dir + 1;
    }
  }
}

BST min_BST(BST root){
    while(root->esq){
        root = root->esq;
    }

    return root;
}
BST max_BST(BST root){
    while(root->dir){
        root = root->dir;
    }

    return root;
}

void bstInOrder(BST cell){
  if(cell == NULL){
      return;
  }
  bstInOrder(cell->esq);
  printf("%d", cell->info);
  bstInOrder(cell->dir);
}

void bstPreOrder(BST cell){
  if(cell == NULL){
      return;
  }
  printf("%d", cell->info);
  bstPreOrder(cell->esq);
  bstPreOrder(cell->dir);
}

void bstPostOrder(BST cell){
  if(cell == NULL){
      return;
  }
  bstPostOrder(cell->esq);
  bstPostOrder(cell->dir);
  printf("%d", cell->info);
}

void GarbageCollection(BST root){
    if(root){
        GarbageCollection(root->esq);
        GarbageCollection(root->dir);
        free(root);
    }
}

//BST AVL
typedef struct AVLnode{
  int infoAVL;
  struct AVLnode * esq;
  struct AVLnode * dir;
  int AVLHeight;
}AVLnode;

typedef AVLnode * AVL;

AVL AVLNewNode(int info){
  AVL newAVL = malloc(sizeof(AVLnode));
  newAVL->infoAVL = info;
  newAVL->esq = NULL;
  newAVL->dir = NULL;
  newAVL->AVLHeight = 1;
  return newAVL;
}

unsigned AVLNodeHeight(AVL node) {
    if (!node) return 0;
    return node->AVLHeight;
}

int AVLHeight(AVL node) {
    return 1 + MAX(AVLNodeHeight(node->esq), AVLNodeHeight(node->dir));
}

int AVLBalanceFactor(AVL node){
  return (AVLNodeHeight(node->esq) - (AVLNodeHeight(node->dir)));
}

AVL rotL(AVL node) {
    AVL Aux;
    Aux = node->dir;
    node->dir = Aux->esq;
    Aux->esq = node;
    node->AVLHeight = AVLHeight(node);
    Aux->AVLHeight = AVLHeight(Aux);
    return Aux;
}

AVL rotR(AVL node) {
    AVL Aux;
    Aux = node->esq;
    node->esq = Aux->dir;
    Aux->dir = node;
    node->AVLHeight = AVLHeight(node);
    Aux->AVLHeight = AVLHeight(Aux);
    return Aux;
}

AVL AVLInsert(AVL root, int info) {
    if (!root) return AVLNewNode(info);
    else if (root->infoAVL == info) return root;
    else if (root->infoAVL > info)
        root->esq = AVLInsert(root->esq, info);
    else
        root->dir = AVLInsert(root->dir, info);

    root->AVLHeight = AVLHeight(root);
    int fator = AVLBalanceFactor(root);

    if (fator == +2) {
        if (AVLBalanceFactor(root->esq) < 0)
            root->esq = rotL(root->esq);
        root = rotR(root);
    }
    else if (fator == -2) {
        if (AVLBalanceFactor(root->dir) > 0)
            root->dir = rotR(root->dir);
        root = rotL(root);
    }
    return root;
}

void libera_AVL(AVL root) {
    if (root != NULL) {
        libera_AVL(root->esq);
        libera_AVL(root->dir);
        free(root);
    }
}

int main() {
    int opcao, amostra, elemento;
    float media_BST = 0, media_AVL = 0, media_geral = 0;
    double media_tempo_AVL = 0, media_tempo_BST = 0, media_tempo_geral = 0;

    srand(time(NULL));
    clock_t inicio_BST, final_BST;
    double tempo_BST;
    clock_t inicio_AVL, final_AVL;
    double tempo_AVL;


    // LOOP DO PROGRAMA
    do{
        printf("\n\n--------------------------------------------------------------------\n");
        printf("1 - Nova Simulação\n2 - Sair\nDigite sua escolha: ");
        scanf("%d", &opcao);
        fflush(stdin);

        switch(opcao){
        case 1:
            printf("\nDigite a quantidade de amostras: ");
            scanf("%d", &amostra);
            fflush(stdin);

            printf("Digite a quantidade de elementos para cada amostra: ");
            scanf("%d", &elemento);
            printf("\n");
            fflush(stdin);

            //INICIA AS ARVORES
            BST raiz_BST[amostra];
            AVL raiz_AVL[amostra];
            for(int i = 0; i < amostra; i++){
               raiz_BST[i] = NULL;
               raiz_AVL[i] = NULL;
            }

            //CRIA VETOR COM VALORES ALEATÓRIOS
            int v[amostra][elemento];
            for(int i = 0; i < amostra; i++){
                    for(int j = 0; j < elemento; j++){
                        v[i][j] = 1  + rand() % 99;
                }
            }

            //INSERE VALORES ALEATÓRIOS NAS ARVORES
            for(int i = 0; i < amostra; i++){
                for(int j = 0; j < elemento; j++){

                    //EXPERIMENTO NA ARVORE BST COMUM
                    inicio_BST = clock();
                    raiz_BST[i] = bstInsert(raiz_BST[i], v[i][j]);
                    final_BST = clock();
                    tempo_BST = ((double) (final_BST-inicio_BST)/CLOCKS_PER_SEC);
                    media_tempo_BST += tempo_BST;

                    //EXPERIMENTO NA ARVORE AVL
                    inicio_AVL = clock();
                    raiz_AVL[i] = AVLInsert(raiz_AVL[i], v[i][j]);
                    final_AVL = clock();
                    tempo_AVL = ((double) (final_AVL-inicio_AVL)/CLOCKS_PER_SEC);
                    media_tempo_AVL += tempo_AVL;
                }

                media_geral = ((media_BST  / amostra) + (media_AVL / amostra)) / 2;
                media_BST += bstHeight(raiz_BST[i]);
                media_AVL += AVLHeight(raiz_AVL[i]);
                media_tempo_geral = ((media_tempo_AVL / amostra) + (media_tempo_BST / amostra)) / 2;

            }

            //RETORNO DE TODOS OS TESTES
            printf("\n");
            printf("Experimento com A = %d e N = %d\n", amostra, elemento);

            printf("\nAltura média geral: %.2f\n", media_geral);
            printf("Tempo médio geral de construção: %lf\n\n", media_tempo_geral);

            printf("Altura média BST comum: %.2f\n", media_BST / amostra);
            printf("Tempo médio de construção BST comum: %lf\n\n", media_tempo_BST / amostra);

            printf("Altura média AVL: %.2f\n", media_AVL / amostra);
            printf("Tempo médio de construção AVL: %lf\n\n", media_tempo_AVL / amostra);
            printf("\n");
            break;
        }

    }while(opcao != 2);

    printf("Encerrando...");

    return 0;
}