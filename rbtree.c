
#include <stdlib.h>
#include <stdio.h>
#include "rbtree.h"

RBTree RBTree_new();
void addRB(RBTree *rbTree, int k);
void arrumarInsercao(RBTree *rbTree, RBTreeNode *x);
void leftRotate(RBTree *rbTree, RBTreeNode *x);
void rightRotate(RBTree *rbTree, RBTreeNode *x);
void disp(RBTree *rbTree);
void display(RBTree *rbTree, RBTreeNode *p);
void del(RBTree *rbTree, int k);
void delRB(RBTreeNode *x, int k);

void addRB(RBTree *rbTree, int k)
{
    RBTreeNode *novo = RBNode_new();
    novo->value = k;
    novo->left = rbTree->root;
    novo->right = rbTree->root;

    if (rbTree->root->right == NULL)
    {
        rbTree->root->right = novo;
        novo->father = rbTree->root;
    }
    else
    {
        RBTreeNode *aux, *pai;
        // printf("%d", rbTree->root->value);
        aux = rbTree->root->right; //ERRO AQUI
        // printf("%d", aux->value);
        while (aux != rbTree->root)
        { //OU AQUI
            pai = aux;
            if (k < aux->value) //ERRO AQUI
                aux = aux->left;
            else
                aux = aux->right;
        }
        if (k < pai->value)
            pai->left = novo;
        else
            pai->right = novo;
        novo->father = pai;
    }
    arrumarInsercao(rbTree, novo);
}
void arrumarInsercao(RBTree *rbTree, RBTreeNode *x)
{
    RBTreeNode *pai = x->father, *tio, *avo;

    while (pai->color == RED)
    {
        avo = pai->father;

        if (x->value < avo->value)
        {
            tio = avo->right;
            //caso 1
            if (tio->color == RED)
            {
                pai->color = BLACK;
                tio->color = BLACK;
                avo->color = RED;
                //x = avo;
                //pai = x->father;
                arrumarInsercao(rbTree, avo);
            }
            else
            {
                //caso 2
                if (x == pai->right)
                {
                    x = pai;
                    leftRotate(rbTree, x);
                }
                //caso 3
                pai->color = BLACK;
                avo->color = RED;
                rightRotate(rbTree, avo);
            }
        }
        else
        {
            tio = avo->left;
            //caso 1
            if (tio->color == RED)
            {
                pai->color = BLACK;
                tio->color = BLACK;
                avo->color = RED;
                //x = avo;
                //pai = x->father;
                arrumarInsercao(rbTree, avo);
            }
            else
            {
                //caso 2
                if (x == pai->left)
                {
                    x = pai;
                    rightRotate(rbTree, x);
                }
                //caso 3
                pai->color = BLACK;
                avo->color = RED;
                leftRotate(rbTree, avo);
            }
        }
    }
    rbTree->root->right->color = BLACK;
}
void leftRotate(RBTree *rbTree, RBTreeNode *x)
{
    RBTreeNode *y;
    y = x->right;
    x->right = y->left;
    if (y->left != rbTree->root)
        y->left->father = x;
    y->father = x->father;
    if (x->father == rbTree->root)
        x->father->right = y;
    else
    {
        if (x == x->father->left)
            x->father->left = y;
        else
            x->father->right = y;
    }
    y->left = x;
    x->father = y;
}
void rightRotate(RBTree *rbTree, RBTreeNode *x)
{
    RBTreeNode *y;
    y = x->left;
    x->left = y->right;

    if (y->right != rbTree->root)
        y->right->father = x;
    y->father = x->father;
    if (x->father == rbTree->root)
        x->father->right = y;
    else
    {
        if (x == x->father->left)
            x->father->left = y;
        else
            x->father->right = y;
    }
    y->right = x;
    x->father = y;
}
void disp(RBTree *rbTree)
{
    if (rbTree->root->right == NULL)
        printf("\nArvore vazia.");
    else
        display(rbTree, rbTree->root->right);
}
void display(RBTree *rbTree, RBTreeNode *p)
{
    if (p != NULL)
    {
        printf("{");
        printf("\"key\": %d,", p->value);
        printf("\"colour\": ");
        if (p->color == BLACK)
            printf("\"black\",");
        else
            printf("\"red\",");


        if (p->left != rbTree->root)
        {
            printf("\"left\": ");
            display(rbTree, p->left);
        }
        if (p->right != rbTree->root)
        {
            printf("\"right\": ");
            display(rbTree, p->right);
        }
        printf("},");
    }
}

void displayBreno(RBTree *rbTree, RBTreeNode *p)
{
    if (p != NULL)
    {
        printf("\n\t NODE: ");
        printf("\n Key: %d", p->value);
        printf("\n Colour: ");
        if (p->color == BLACK)
            printf("Black");
        else
            printf("Red");
        if (p->father != NULL)
            printf("\n Parent: %d", p->father->value);
        else
            printf("\n There is no parent of the node.  ");
        if (p->right != NULL)
            printf("\n Right Child: %d", p->right->value);
        else
            printf("\n There is no right child of the node.  ");
        if (p->left != NULL)
            printf("\n Left Child: %d", p->left->value);
        else
            printf("\n There is no left child of the node.  ");

        if (p->left != rbTree->root)
        {
            printf("\n\nLeft:\n");
            display(rbTree, p->left);
        }
        /*else
     cout<<"\nNo Left Child.\n";*/
        if (p->right != rbTree->root)
        {
            printf("\n\nRight:\n");
            display(rbTree, p->right);
        }
        /*else
     cout<<"\nNo Right Child.\n"*/
    }
}
void del(RBTree *rbTree, int k)
{
    if (rbTree->root->right == NULL)
        printf("\nArvore vazia.");
    else
        delRB(rbTree->root->right, k);
}
void delRB(RBTreeNode *x, int k)
{
    //Procura a chave
    while (x->value != -1000 && x->value != k)
    {
        if (x->value < k)
            x = x->right;
        else
            x = x->left;
    }
    //Testa se n�o chegou no final da arvore
    if (x->value == -1000)
    {
        printf("\nO valor nao foi encontrado.");
        return;
    }
    //achou a arvore e vai testar as cores
    else
    {
        if (x->left->left != NULL)
        { //Tem filho esquerdo
            //            x->value = getSuccRB();
            delRB(x->left, x->value);
        }
        else if (x->right->left != NULL)
        { //Tem filho direito
            //            x->value = getPredRB();
            delRB(x->right, x->value);
        }
        else
        { //Eh folha
            if (x->color == RED)
            {
                if (x->father->right == x)
                {
                    x->father->right = x->right; //nao sei se t� certo isso aqui, talvez tenha q ser ponteiro???
                    free(x);
                }
                else
                {
                    x->father->left = x->right; //nao sei se t� certo isso aqui, talvez tenha q ser ponteiro???
                    free(x);
                }
            }
            else
            {
                if (x->father->left == x)
                {
                    RBTreeNode *w = x->father->right;
                    if (w->color == RED)
                    {
                        w->color = BLACK;
                        x->father->color = RED;
                        //rightRotate()
                    }
                }
                else
                {
                }
            }
        }
    }
}

RBTree RBTree_new()
{
    RBTree rbTree;
    rbTree.root = RBTreeRoot();
    rbTree.add = &addRB;
    rbTree.del = &del;
    //rbTree.root.value = -1000;
    return rbTree;
}
//http://www.lcad.icmc.usp.br/~nonato/ED/Arvore_Binaria/node66.html
//https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
//https://www.coders-hub.com/2015/07/red-black-tree-rb-tree-using-c.html#.W7AFI2hKjIV
//https://www.sanfoundry.com/cpp-program-implement-red-black-tree/
//https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/
