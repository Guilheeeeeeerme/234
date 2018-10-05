#include "rbtree-node.h"

typedef struct RBTree
{
    RBTreeNode *root;
    void (*add)(struct RBTree *, int);
    void (*del)(struct RBTree *, int);
} RBTree;

RBTree RBTree_new();
//void addRB(RBTree*, int);
void disp(RBTree *);
