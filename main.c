#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include "rbtree.h"

void menuBtree();
void menuRBtree();

void menuBtree() {
    int opcao, k;
    BTree bTree = BTree__new();
    while(1){
        printf("1.Inserir novo elemento na arvore 2-3-4\n");
        printf("2.Remover elemento da arvore 2-3-4\n");
        printf("3.Imprimir arvore 2-3-4\n");
        printf("4.Converter em uma arvore rubro-negra\n");
        printf("5.Sair\n");
        printf("Enter your choice : ");
        scanf("%d",&opcao);

        switch(opcao){
            case 1:
                printf("Digite a chave : ");
                scanf("%d",&k);
                bTree.add(&bTree, k);
                system("cls");
                break;
            case 2:
                printf("Digite a chave : ");
                scanf("%d",&k);
                bTree.del(&bTree, k);
                system("cls");
                break;
            case 3:
                system("cls");
                bTree.show(&bTree);
                printf("\n");
                traverse(bTree.root);
                printf("\n\n\n\n");

                break;
            case 4:
                system("cls");
                menuRBtree();
                exit(1);
                break;
            case 5:
                exit(1);
                break;
            default:
                printf("Opcao errada");
                break;
        }
    }
}
void menuRBtree() {
    int opcao, k;
    RBTree rbTree = RBTree_new();
    while(1){
        printf("1.Inserir novo elemento na arvore rubro-negra\n");
        printf("2.Remover elemento da �rvore rubro-negra\n");
        printf("3.Imprimir arvore rubro-negra\n");
        printf("4.Sair\n");
        printf("Enter your choice : ");
        scanf("%d",&opcao);

        switch(opcao){
            case 1:
                printf("Digite a chave : ");
                scanf("%d",&k);
                rbTree.add(&rbTree, k);
                system("cls");
                break;
            case 2:
                printf("Digite a chave : ");
                scanf("%d",&k);
                rbTree.del(&rbTree, k);
                system("cls");
                break;
            case 3:
                system("cls");
                //bTree.show(&rbTree);
                printf("\n");
                disp(&rbTree);
                //traverse(bTree.root);
                printf("\n\n\n\n");
                break;
            case 4:
                exit(1);
                break;
            default:
                printf("Opcao errada");
                break;
        }
    }
}
int main() {
    BTree bTree = BTree__new();
    RBTree rbTree = RBTree_new();

    menuBtree();



/*
    for(int i =0; i< 10; i++)
        bTree.add(&bTree, i);

    printf("var bTree = ");
    bTree.show(&bTree);*/

    //BTreeNode_show(bTree.root);


    ///////////////////////////////

   /* BTreeNode* nodeBusca = BTreeNode__new();

    printf("\nInsira o valor a ser pesquisado: ");
    scanf("%d", &k);
    busca = BTreeSearch(bTree.root, k, nodeBusca);

    if(busca == -1){
        printf("\nnada foi encontrado");
    }
    else{
    printf("\nO node eh:\n");
    BTreeNode_show(nodeBusca);
    printf("\nO indice eh: %d\n",busca);*/


  /////////////////////

    /*BTreeNode_show(nodeBusca->parent);
    printf("\n");
    int hh = 0;
    while(nodeBusca->parent->n+3 > hh){
        printf("\n");
        BTreeNode_show(nodeBusca->parent->children[hh]);
        hh++;
    }*/
    //BTreeNode_show(nodeBusca->parent->children[nodeBusca->parent->n]);
    //free(nodeBusca);
    //}









    ////////////////////////////
     /*BTreeNode* nodeFilho = BTreeNode__new();
    nodeBusca->leaf = FALSE;
    printf("\nInsira o filho a ser pesquisado: ");
    scanf("%d", &k);
    busca2 = precedingChild(bTree.root,k,nodeFilho);

    if(busca2 == -1){
        printf("\nnada foi encontrado");
    }
    else{
    printf("\nO node eh:\n");
    BTreeNode_show(nodeFilho);
    printf("\nO indice eh: %d\n",busca2);
    }*/
    //////////////////////
    /*printf("\n");
    traverse(bTree.root);
    int mn = 1;
    while(mn!=0){
        printf("\nInsira o valor a ser deletado: ");
        scanf("%d", &k);
        removeT(&bTree, k);
        bTree.show(&bTree);
        printf("\n");
        traverse(bTree.root);
        //printf("\nDigite 0 para parar: ");
        //scanf("%d", &mn);
    }*/


    return 0;
}
