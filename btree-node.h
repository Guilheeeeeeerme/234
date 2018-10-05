#define T 2
#define ORDER (2 * T)-1
#define CHILDREN (ORDER+1)
#define TRUE 1
#define FALSE 0

typedef struct BTreeNode {
    int leaf;
    int n;
    int keys[ORDER];
    struct BTreeNode *parent;
    struct BTreeNode *children[CHILDREN];
} BTreeNode;

BTreeNode* BTreeNode__new();
int BTreeNode__isLeaf(BTreeNode* root);
int BTreeNode__isFull(BTreeNode* root);
