#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include "rbtree.h"

int DEBUG = 0;

void menuBtree();
void menuRBtree();
void converterParaRb(BTreeNode *bTreeNode, RBTree *rbTree);

int main(int argc, char *argv)
{

    if (argc > 1)
    {
        DEBUG = 1;
    }

    BTree bTree = BTree__new();
    RBTree rbTree = RBTree_new();
    int opcao;

    if (DEBUG == 1)
        printf("1. 2-3-4\n");
    if (DEBUG == 1)
        printf("2. Rubro Negra\n");
    if (DEBUG == 1)
        printf("Enter your choice : ");
    scanf("%d", &opcao);

    if (opcao == 1)
    {
        menuBtree(&bTree);
    }
    else if (opcao == 2)
    {
        menuRBtree(&rbTree);
    }

    return 0;
}

void menuBtree(BTree *bTree)
{
    int opcao, k;
    RBTree rbTree;

    do
    {
        if (DEBUG == 1)
            printf("1.Inserir novo elemento na arvore 2-3-4\n");
        if (DEBUG == 1)
            printf("2.Remover elemento da arvore 2-3-4\n");
        if (DEBUG == 1)
            printf("3.Imprimir arvore 2-3-4\n");
        if (DEBUG == 1)
            printf("4.Converter em uma arvore rubro-negra\n");
        if (DEBUG == 1)
            printf("5.Sair\n");
        if (DEBUG == 1)
            printf("Enter your choice : ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            if (DEBUG == 1)
                printf("Digite um valor: ");
            scanf("%d", &k);
            bTree->add(bTree, k);
            break;
        case 2:
            if (DEBUG == 1)
                printf("Digite um valor: ");
            scanf("%d", &k);
            bTree->del(bTree, k);
            break;
        case 3:
            bTree->show(bTree);
            break;
        case 4:
            rbTree = RBTree_new();
            converterParaRb(bTree->root, &rbTree);
            disp(&rbTree);
            break;
        case 5:
            break;
        default:
            if (DEBUG == 1)
                printf("Opcao errada");
            break;
        }

    } while (opcao != 5);
}

void menuRBtree(RBTree *rbTree)
{
    int opcao, k;

    do
    {
        if (DEBUG == 1)
            printf("1.Inserir novo elemento na arvore rubro-negra\n");
        if (DEBUG == 1)
            printf("2.Remover elemento da arvore rubro-negra\n");
        if (DEBUG == 1)
            printf("3.Imprimir arvore rubro-negra\n");
        if (DEBUG == 1)
            printf("4.Sair\n");
        if (DEBUG == 1)
            printf("Enter your choice : ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            if (DEBUG == 1)
                printf("Digite um valor: ");
            scanf("%d", &k);
            rbTree->add(rbTree, k);
            break;
        case 2:
            if (DEBUG == 1)
                printf("Digite um valor: ");
            scanf("%d", &k);
            rbTree->del(rbTree, k);
            break;
        case 3:
            disp(rbTree);
            break;
        case 4:
            break;
        default:
            if (DEBUG == 1)
                printf("Opcao errada");
            break;
        }
    } while (opcao != 4);
}

void converterParaRb(BTreeNode *bTreeNode, RBTree *rbTree)
{

    if (bTreeNode->n == 1)
    {
        rbTree->add(rbTree, bTreeNode->keys[0]);
    }
    else if (bTreeNode->n == 2)
    {
        rbTree->add(rbTree, bTreeNode->keys[0]);
        rbTree->add(rbTree, bTreeNode->keys[1]);
    }
    else if (bTreeNode->n == 3)
    {
        rbTree->add(rbTree, bTreeNode->keys[1]);
        rbTree->add(rbTree, bTreeNode->keys[0]);
        rbTree->add(rbTree, bTreeNode->keys[2]);
    }

    if (bTreeNode->leaf == FALSE)
    {
        for (int i = 0; i <= bTreeNode->n; i++)
        {
            converterParaRb(bTreeNode->children[i], rbTree);
        }
    }
}
