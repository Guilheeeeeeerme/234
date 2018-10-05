#include "rbtree.h"
#include <stdlib.h>

RBTreeNode* RBNode_new(){
    RBTreeNode* rbTreeNode = (RBTreeNode*) malloc (sizeof(RBTreeNode));
    rbTreeNode->color = RED;
    rbTreeNode->father = NULL;
    rbTreeNode->left = NULL;
    rbTreeNode->right = NULL;

    return rbTreeNode;
}

RBTreeNode* RBTreeRoot(){
    RBTreeNode* rbTreeRoot = (RBTreeNode*) malloc (sizeof(RBTreeNode));
    rbTreeRoot->value = -1000;
    rbTreeRoot->color = BLACK;
    rbTreeRoot->father = NULL;
    rbTreeRoot->left = NULL;
    rbTreeRoot->right = NULL;

    return rbTreeRoot;
}


