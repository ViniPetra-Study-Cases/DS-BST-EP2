#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node{
    int info;
    //int h; //altura
    struct node* esq;
    struct node* dir;
}Node;
typedef Node* Cell;

Cell bstNewNode(int value){
    Cell node = malloc(sizeof(Cell));
    node->dir = NULL;
    node->esq = NULL;
    node->info = value;
    return node;
}

Cell bstSearch(Cell root, int target){
    if(root == NULL || root->info == target){
        return root;
    }
    else if(target > root->info){
        return bstSearch(root->dir, target);
    }
    else
    {
        return bstSearch(root->esq, target);
    }
}

Cell bstMin(Cell root) {
    if (root == NULL || root->esq == NULL) {
        return root;
    }
    else
    {
        return bstMin(root->esq);
    }
}

Cell bstMax(Cell root){
    if (root == NULL || root->dir == NULL) {
        return root;
    }
    else
    {
        return bstMax(root->dir);
    }
}

Cell bstInsert(Cell root, int value){
    if(root == NULL){
        return bstNewNode(value);
    }else if(value > root->info){
        root->dir = bstInsert(root->dir, value);
    }else {
        root->esq = bstInsert(root->esq, value);
    }
}

int bstHeight(Cell root){
    if(root == NULL) {
        return 0;
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

int bstBalanceFactor(Cell cell){
    return (bstHeight(cell->esq) - (bstHeight(cell->dir)));
}

//https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
///Algorithm Inorder(tree)
//1. Traverse the left subtree, i.e., call Inorder(left-subtree)
//2. Visit the root.
//3. Traverse the right subtree, i.e., call Inorder(right-subtree)
void bstInOrder(Cell cell){
    if(cell == NULL){
        return;
    }
    bstInOrder(cell->esq);
    printf("%d", cell->info);
    bstInOrder(cell->dir);
}

///Algorithm Preorder(tree)
//1. Visit the root.
//2. Traverse the left subtree, i.e., call Preorder(left-subtree)
//3. Traverse the right subtree, i.e., call Preorder(right-subtree)
void bstPreOrder(Cell cell){
    if(cell == NULL){
        return;
    }
    printf("%d", cell->info);
    bstPreOrder(cell->esq);
    bstPreOrder(cell->dir);
}

///Algorithm Postorder(tree)
//1. Traverse the left subtree, i.e., call Postorder(left-subtree)
//2. Traverse the right subtree, i.e., call Postorder(right-subtree)
//3. Visit the root.
void bstPostOrder(Cell cell){
    if(cell == NULL){
        return;
    }
    bstPostOrder(cell->esq);
    bstPostOrder(cell->dir);
    printf("%d", cell->info);
}

//https://ranger.uta.edu/~alex/courses/3318/lectures/08_search_BST.pdf

Cell bstRotL (Cell cell){
    Cell x = cell->dir;
    cell->dir = x->esq;
    x->esq = cell;
    return x;
}

Cell bstRotR (Cell cell){
    Cell x = cell->esq;
    cell->esq = x->dir;
    x->dir = cell;
    return x;
}

int main() {
    printf("Hello, World!\n");
    return 0;
}

