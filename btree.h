
#include "btree-node.h"

typedef struct BTree
{
    BTreeNode *root;
    void (*add)(struct BTree *self, int key);
    void (*show)(struct BTree *self);
    void (*del)(struct BTree *self, int);
} BTree;

BTree BTree__new();
void traverse(BTreeNode *x);
