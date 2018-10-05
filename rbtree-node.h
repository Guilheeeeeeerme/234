
#define BLACK 1
#define RED 0





typedef struct RBTreeNode {
    int value;
    int color;
    struct RBTreeNode *left, *right, *father;
} RBTreeNode;


RBTreeNode* RBNode_new();
RBTreeNode* RBTreeRoot();





