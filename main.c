#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include "rbtree.h"

RBTree menuBtree(BTree *bTree);
void menuRBtree();
RBTreeNode *converterParaRb(BTreeNode *bTreeNode, RBTreeNode *father, RBTreeNode *root);

int main(int argc, char **argv)
{

    int num;
    FILE *fp;
    BTree bTree = BTree__new();
    RBTree rbTree = RBTree_new();

    // Recebe o arquivo de entrada, com os valores numéricos que serão armazenados na árvore 2-3-4.
    if (argc >= 2)
    {
        fp = fopen(argv[1], "r");
    }
    else
    {

        fp = fopen("input.in", "r");

        if (fp == NULL)
        {
            printf("usage %s <filename>", argv[0]);
            exit(0);
        }
    }

    // Ao ler o arquivo de entrada, o programa deverá gerar a árvore 2-3-4
    while (fscanf(fp, "%d", &num) != EOF)
    {
        bTree.add(&bTree, num);
    }

    // mostrá-la na tela
    printf("\n");
    printf("\n");
    bTree.show(&bTree);
    printf("\n");
    printf("\n");

    // e apresentar o seguinte menu:
    rbTree = menuBtree(&bTree);

    printf("\n");
    printf("\n");
    disp(&rbTree);
    printf("\n");
    printf("\n");

    // mostrá-la na tela, informando a chave e sua respectiva cor e apresentar o seguinte menu:
    menuRBtree(&rbTree);
    return 0;
}

RBTree menuBtree(BTree *bTree)
{
    int opcao, k;
    RBTree rbTree;

    do
    {

        printf("1.Inserir novo elemento na arvore 2-3-4\n");

        printf("2.Remover elemento da arvore 2-3-4\n");

        printf("3.Imprimir arvore 2-3-4\n");

        printf("4.Converter em uma arvore rubro-negra\n");

        printf("5.Sair\n");

        printf("Enter your choice : ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:

            printf("Digite um valor: ");
            scanf("%d", &k);
            bTree->add(bTree, k);
            break;
        case 2:

            printf("Digite um valor: ");
            scanf("%d", &k);
            bTree->del(bTree, k);
            break;
        case 3:
            printf("\n");
            printf("\n");
            bTree->show(bTree);
            printf("\n");
            printf("\n");
            break;
        case 4:
            rbTree = RBTree_new();
            // Caso o usuário escolha converter a árvore em uma rubro-negra,
            // o programa deverá gerar a rubro negra A PARTIR DA 2-3-4,
            RBTreeNode *novo = converterParaRb(bTree->root, rbTree.root, rbTree.root);

            rbTree.root->right = novo;
            novo->father = rbTree.root;

            return rbTree;
        case 5:
            break;
        default:

            printf("Opcao errada\n");
            break;
        }

    } while (opcao != 5);
}

void menuRBtree(RBTree *rbTree)
{
    int opcao, k;

    do
    {

        printf("1.Inserir novo elemento na arvore rubro-negra\n");

        printf("2.Remover elemento da arvore rubro-negra\n");

        printf("3.Imprimir arvore rubro-negra\n");

        printf("4.Sair\n");

        printf("Enter your choice : ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:

            printf("Digite um valor: ");
            scanf("%d", &k);
            rbTree->add(rbTree, k);
            break;
        case 2:

            printf("Digite um valor: ");
            scanf("%d", &k);
            rbTree->del(rbTree, k);
            break;
        case 3:
            printf("\n");
            printf("\n");
            disp(rbTree);
            printf("\n");
            printf("\n");
            break;
        case 4:
            break;
        default:

            printf("Opcao errada\n");
            break;
        }
    } while (opcao != 4);
}

RBTreeNode *converterParaRb(BTreeNode *bTreeNode, RBTreeNode *father, RBTreeNode *root)
{

    RBTreeNode *novo = RBNode_new();
    RBTreeNode *left = RBNode_new();
    RBTreeNode *right = RBNode_new();

    if (!bTreeNode)
    {
        return root;
    }

    if (bTreeNode->n == 1)
    {
        novo->father = father;
        novo->color = BLACK;
        novo->value = bTreeNode->keys[0];
        novo->left = converterParaRb(bTreeNode->children[0], novo, root);
        novo->right = converterParaRb(bTreeNode->children[1], novo, root);
    }
    else if (bTreeNode->n == 2)
    {
        novo->father = father;
        novo->color = BLACK;
        novo->value = bTreeNode->keys[1];
        novo->right = converterParaRb(bTreeNode->children[2], novo, root);

        left->father = novo;
        left->color = RED;
        left->value = bTreeNode->keys[0];
        left->left = converterParaRb(bTreeNode->children[0], left, root);
        left->right = converterParaRb(bTreeNode->children[1], left, root);

        novo->left = left;
    }
    else if (bTreeNode->n == 3)
    {
        novo->father = father;
        novo->color = BLACK;
        novo->value = bTreeNode->keys[1];
        novo->right = converterParaRb(bTreeNode->children[2], novo, root);

        left->father = novo;
        left->color = RED;
        left->value = bTreeNode->keys[0];
        left->left = converterParaRb(bTreeNode->children[0], left, root);
        left->right = converterParaRb(bTreeNode->children[1], left, root);

        right->father = novo;
        right->color = RED;
        right->value = bTreeNode->keys[2];
        right->left = converterParaRb(bTreeNode->children[2], right, root);
        right->right = converterParaRb(bTreeNode->children[3], right, root);

        novo->left = left;
        novo->right = right;
    }

    return novo;
}
