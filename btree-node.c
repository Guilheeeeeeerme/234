#include <stdio.h>
#include <stdlib.h>
#include "btree-node.h"

BTreeNode *BTreeNode__new()
{

    BTreeNode *bTreeNode = (BTreeNode *)malloc(sizeof(BTreeNode));

    bTreeNode->n = 0;
    bTreeNode->leaf = TRUE;
    bTreeNode->parent = NULL;

    for (int i = 0; i < (CHILDREN); i++)
    {
        bTreeNode->children[i] = NULL;
    }

    return bTreeNode;
}

int BTreeNode__isLeaf(BTreeNode *root)
{
    return root->leaf == TRUE;
}

int BTreeNode__isFull(BTreeNode *root)
{
    return root->n == (ORDER - 1);
}
