#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include "array.h"

int getSucc(BTreeNode *x, int idx);
void merge(BTreeNode *x, int idx);
void BTreeSplitChild (BTreeNode* target, int insertAt);
void BTreeInsertNonfull (BTreeNode* x, int k);
int BTreeSearch (BTreeNode* x, int k, BTreeNode* y);
int precedingChild(BTreeNode* x, int k, BTreeNode* y);
int successorChild(BTreeNode* x, int k, BTreeNode* y);
void replaceNode(int k, BTreeNode* x, int k1, BTreeNode* y);
void traverse(BTreeNode *x);
void removeT(BTree *tree, int k);
void removeNode(BTreeNode* x, int k);
void fill(BTreeNode *x, int idx);
void borrowFromNext(BTreeNode *x, int idx);
void borrowFromPrev(BTreeNode *x, int idx);
int findKey(BTreeNode *x, int k);
void removeFromLeaf (BTreeNode *x, int idx);
void removeFromNonLeaf(BTreeNode *x, int idx);
int getPred(BTreeNode *x, int idx);
void BTreeNode_show(BTreeNode* x);
void BTreeNode__show(BTreeNode* x);
void show(BTree* self);
void addB(BTree* self, int k);
BTree BTree__new();

int getSucc(BTreeNode *x, int idx){

    // Keep moving the left most node starting from C[idx+1] until we reach a leaf
    BTreeNode *cur = x->children[idx+1];
    printf("%d",x->children[idx]->leaf);
    while (!cur->leaf)  //ERRO AQUI
        cur = cur->children[0];

    // Return the first key of the leaf
    return cur->keys[0];
}
void merge(BTreeNode *x, int idx){
    BTreeNode *child = x->children[idx];
    BTreeNode *sibling = x->children[idx+1];

    // Pulling a key from the current node and inserting it into (t-1)th
    // position of C[idx]
    child->keys[T-1] = x->keys[idx];

    // Copying the keys from C[idx+1] to C[idx] at the end
    for (int i=0; i<sibling->n; ++i)
        child->keys[i+T] = sibling->keys[i];

    // Copying the child pointers from C[idx+1] to C[idx]
    if (!child->leaf)
    {
        for(int i=0; i<=sibling->n; ++i)
            child->children[i+T] = sibling->children[i];
    }

    // Moving all keys after idx in the current node one step before -
    // to fill the gap created by moving keys[idx] to C[idx]
    for (int i=idx+1; i<x->n; ++i)
        x->keys[i-1] = x->keys[i];

    // Moving the child pointers after (idx+1) in the current node one
    // step before
    for (int i=idx+2; i<=x->n; ++i)
        x->children[i-1] = x->children[i];

    // Updating the key count of child and the current node
    child->n += sibling->n+1;
    x->n--;

    // Freeing the memory occupied by sibling
    free(sibling);
}
void BTreeSplitChild (BTreeNode* target, int insertAt){

    BTreeNode* right = BTreeNode__new(); // z
    BTreeNode* left = target->children[insertAt];

    right->leaf = left->leaf;

    right->n = T - 1;
    for(int j = 0; j < right->n ; j++){
        right->keys[j] = left->keys[j+T];
    }

    if(!left->leaf){
        for(int j = 0; j < T; j++){
            right->children[j] = left->children[j+T];
        }
    }

    left->n = T - 1;

    for(int j = (target->n - 1); j > insertAt + 1; j--){
        target->children[j+1] = target->children[j];
    }

    target->children[insertAt+1] = right;

    for(int j = target->n; j > insertAt; j-- ){
        target->keys[j] = target->keys[j-1];
    }

    target->keys[insertAt] = left->keys[T-1];
    target->n++;
    right->parent = target;
    left->parent = target;

}
void BTreeInsertNonfull (BTreeNode* x, int k){

    if(x->leaf){
        x->keys[x->n] = k;
        x->n++;
        insertionSort(x->keys, x->n);
    }else{
        int i = x->n;

        while(i > 0 && k < x->keys[i-1] ){
            i--;
        }

        if( x->children[i]->n == ((2 * T) - 1) ){
            BTreeSplitChild(x, i);
            if(k > x->keys[i]){
                i = i + 1;
            }
        }
        BTreeInsertNonfull(x->children[i], k);
    }
}
int BTreeSearch (BTreeNode* x, int k, BTreeNode* y){
        int i = 0;
        while((i < x->n) && (k > x->keys[i]) ){
            i++;
        }
        if(i < x->n && k == x->keys[i]){
            *y = *x;
            return i;
        }
        else if(x->leaf){
            return (-1);
        }
        else{
            return BTreeSearch(x->children[i], k, y);
        }
}
int precedingChild(BTreeNode* x, int k, BTreeNode* y){
    int k1, j, i;
        j = k;
        k1 = -1;
        while(k1==-1 && j>=0){
            k1 = BTreeSearch(x,j-1,y);
            printf("%d\n",k1);
            printf("%d\n",j);
            j--;
        }
        if(j<0){
            return -1;
        }
        else{
            return k1;
        }
}
int successorChild(BTreeNode* x, int k, BTreeNode* y){
    int k1, j, i;
        j = k;
        k1 = -1;
        while(k1==-1 && j>=0){
            k1 = BTreeSearch(x,j-1,y);
            printf("%d\n",k1);
            printf("%d\n",j);
            j--;
        }
        if(j<0){
            return -1;
        }
        else{
            return k1;
        }
}
void replaceNode(int k, BTreeNode* x, int k1, BTreeNode* y){
    int i, i2;
    BTreeNode* aux = BTreeNode__new();
    i = BTreeSearch(x,k,aux);
    BTreeNode* aux2 = BTreeNode__new();
    i = BTreeSearch(y,k1,aux2);
    x->n--;
    y->keys[i2] = x->keys[i];
    // x->keys[i] = NULL;
    insertionSort(x->keys, x->n);
    free(aux);
    free(aux2);
}
void traverse(BTreeNode *x){
    // There are n keys and n+1 children, travers through n keys
    // and first n children
    int i;
    for (i = 0; i < x->n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (x->leaf == FALSE)
            traverse(x->children[i]);
        printf(" %d", x->keys[i]);
    }

    // Print the subtree rooted with last child
    if (x->leaf == FALSE)
        traverse(x->children[i]);
}
void removeT(BTree *tree, int k){
    if (!tree->root)
    {
        printf("A arvore esta vazia\n");
        //cout << "The tree is empty\n";
        return;
    }

    // Call the remove function for root
    removeNode(tree->root, k);

    // If the root node has 0 keys, make its first child as the new root
    //  if it has a child, otherwise set root as NULL
    if (tree->root->n==0)
    {
        //BTreeNode *tmp = tree->root;
        if (tree->root->leaf)
            tree->root = NULL;
        else
            tree->root = tree->root->children[0];

        // Free the old root
        //delete tmp;
    }
    return;
}
void removeNode(BTreeNode* x, int k){
    int idx = findKey(x, k);

    // The key to be removed is present in this node
    if (idx < x->n && x->keys[idx] == k)
    {

        // If the node is a leaf node - removeFromLeaf is called
        // Otherwise, removeFromNonLeaf function is called
        if (x->leaf)
            removeFromLeaf(x, idx);
        else
            removeFromNonLeaf(x, idx);
    }
    else
    {

        // If this node is a leaf node, then the key is not present in tree
        if (x->leaf)
        {
            printf("A chave %d n�o existe na �rvore",k);
            //cout << "The key "<< k <<" is does not exist in the tree\n";
            return;
        }

        // The key to be removed is present in the sub-tree rooted with this node
        // The flag indicates whether the key is present in the sub-tree rooted
        // with the last child of this node
        int flag = ( (idx==x->n)? TRUE : FALSE );

        // If the child where the key is supposed to exist has less that t keys,
        // we fill that child
        if (x->children[idx]->n < T)
            fill(x, idx);

        // If the last child has been merged, it must have merged with the previous
        // child and so we recurse on the (idx-1)th child. Else, we recurse on the
        // (idx)th child which now has atleast t keys
        if (flag && idx > x->n)
            removeNode(x->children[idx-1], k);
        else
            removeNode(x->children[idx], k);
    }
    return;
}
void fill(BTreeNode *x, int idx){

    // If the previous child(C[idx-1]) has more than t-1 keys, borrow a key
    // from that child
    if (idx!=0 && x->children[idx-1]->n>=T)
        borrowFromPrev(x, idx);

    // If the next child(C[idx+1]) has more than t-1 keys, borrow a key
    // from that child
    else if (idx!=x->n && x->children[idx+1]->n>=T)
        borrowFromNext(x, idx);

    // Merge C[idx] with its sibling
    // If C[idx] is the last child, merge it with with its previous sibling
    // Otherwise merge it with its next sibling
    else
    {
        if (idx != x->n)
            merge(x, idx);
        else
            merge(x, idx-1);
    }
    return;
}
void borrowFromNext(BTreeNode *x, int idx){

    BTreeNode *child=x->children[idx];
    BTreeNode *sibling=x->children[idx+1];

    // keys[idx] is inserted as the last key in C[idx]
    child->keys[(child->n)] = x->keys[idx];

    // Sibling's first child is inserted as the last child
    // into C[idx]
    if (!(child->leaf))
        child->children[(child->n)+1] = sibling->children[0];

    //The first key from sibling is inserted into keys[idx]
    x->keys[idx] = sibling->keys[0];

    // Moving all keys in sibling one step behind
    for (int i=1; i<sibling->n; ++i)
        sibling->keys[i-1] = sibling->keys[i];

    // Moving the child pointers one step behind
    if (!sibling->leaf)
    {
        for(int i=1; i<=sibling->n; ++i)
            sibling->children[i-1] = sibling->children[i];
    }

    // Increasing and decreasing the key count of C[idx] and C[idx+1]
    // respectively
    child->n += 1;
    sibling->n -= 1;

    return;
}
void borrowFromPrev(BTreeNode *x, int idx){

    BTreeNode *child=x->children[idx];
    BTreeNode *sibling=x->children[idx-1];

    // The last key from C[idx-1] goes up to the parent and key[idx-1]
    // from parent is inserted as the first key in C[idx]. Thus, the  loses
    // sibling one key and child gains one key

    // Moving all key in C[idx] one step ahead
    for (int i=child->n-1; i>=0; --i)
        child->keys[i+1] = child->keys[i];

    // If C[idx] is not a leaf, move all its child pointers one step ahead
    if (!child->leaf)
    {
        for(int i=child->n; i>=0; --i)
            child->children[i+1] = child->children[i];
    }

    // Setting child's first key equal to keys[idx-1] from the current node
    child->keys[0] = x->keys[idx-1];

    // Moving sibling's last child as C[idx]'s first child
    if(!child->leaf)
        child->children[0] = sibling->children[sibling->n];

    // Moving the key from the sibling to the parent
    // This reduces the number of keys in the sibling
    x->keys[idx-1] = sibling->keys[sibling->n-1];

    child->n += 1;
    sibling->n -= 1;

    return;
}
int findKey(BTreeNode *x, int k){
    int idx=0;
    while (idx<x->n && x->keys[idx] < k)
        ++idx;
    return idx;
}
void removeFromLeaf (BTreeNode *x, int idx){

    // Move all the keys after the idx-th pos one place backward
    for (int i=idx+1; i<x->n; ++i)
        x->keys[i-1] = x->keys[i];

    // Reduce the count of keys
    x->n--;

    return;
}
void removeFromNonLeaf(BTreeNode *x, int idx){

    int k = x->keys[idx];

    // If the child that precedes k (C[idx]) has atleast t keys,
    // find the predecessor 'pred' of k in the subtree rooted at
    // C[idx]. Replace k by pred. Recursively delete pred
    // in C[idx]
    if (x->children[idx]->n >= T)
    {
        //int pred = getPred(x->children[idx], idx);
        int pred = getPred(x, idx);
        x->keys[idx] = pred;
        removeNode(x->children[idx], pred);
    }

    // If the child C[idx] has less that t keys, examine C[idx+1].
    // If C[idx+1] has atleast t keys, find the successor 'succ' of k in
    // the subtree rooted at C[idx+1]
    // Replace k by succ
    // Recursively delete succ in C[idx+1]
    else if  (x->children[idx+1]->n >= T)
    {
        //int succ = getSucc(x->children[idx], idx);
        int succ = getSucc(x, idx);
        x->keys[idx] = succ;
        removeNode(x->children[idx+1], succ);
    }

    // If both C[idx] and C[idx+1] has less that t keys,merge k and all of C[idx+1]
    // into C[idx]
    // Now C[idx] contains 2t-1 keys
    // Free C[idx+1] and recursively delete k from C[idx]
    else
    {
        merge(x, idx);
        removeNode(x->children[idx], k);
    }
    return;
}
int getPred(BTreeNode *x, int idx){
    // Keep moving to the right most node until we reach a leaf
    BTreeNode *cur=x->children[idx];
    while (!cur->leaf)
        cur = cur->children[cur->n];

    // Return the last key of the leaf
    return cur->keys[cur->n-1];
}
void BTreeNode_show(BTreeNode* x){
    printf("{");

    if(x){
        printf("\"leaf\": %d, ", x->leaf);
        printf("\"n\": %d ,", x->n);
        printf("\"keys\": ");
        printArray(x->keys, x->n);


    }

    printf(" } ");
}
void BTreeNode__show(BTreeNode* x){
    printf("{");

    if(x){
        printf("\"leaf\": %d, ", x->leaf);
        printf("\"n\": %d ,", x->n);
        printf("\"keys\": ");
        printArray(x->keys, x->n);
        printf(" ,\"children\": [");

        if(!x->leaf){
            int i;

            for(i = 0; i < x->n; i++){
                BTreeNode__show(x->children[i]);
            }

            BTreeNode__show(x->children[i]);

        }

        printf("]");

    }

    printf(" }, ");
}
void show(BTree* self){
    BTreeNode__show(self->root);
}
void addB(BTree* self, int k){

    BTreeNode* r = self->root;

    if (r->n == ((2 * T) - 1)){
        BTreeNode* s = BTreeNode__new();

        self->root = s;
        s->leaf = FALSE;
        s->n = 0;
        s->children[0] = r;

        BTreeSplitChild(s, 0);
        //r->parent = s;
        BTreeInsertNonfull(s, k);
    } else {
        BTreeInsertNonfull(r, k);
    }

}
BTree BTree__new(){
    BTree bTree;
    bTree.root = BTreeNode__new();
    bTree.add = &addB;
    bTree.show = &show;
    bTree.del = &removeT;
    return bTree;
}
/*void mergeNode(BTreeNode* y,BTreeNode* z,BTreeNode* x,int k){
    int i;
    for(i=0;i<t;i++){
        y->keys[i+t-1] = z[i];
        y->children[i+t] = z->children[i];
    }

}*/

/*void BTreeDelete(BTreeNode* x, int k){
    int k1, k2, j;
    BTreeNode* y = BTreeNode__new();
    BTreeNode* z = BTreeNode__new();
    k1 = precedingChild(x,k,y);
    k2 = successorChild(x,k,z);

    if(!x->leaf){ //n� n�o � folha
        if(y->n > (t-1)){
            replaceNode(k1,y,k,x);
            //replaceNode(k,x,z);
            //BTreeDelete(k,z);
        }
        else if(z->n > (t-1)){
            replaceNode(k1,z,k,x);
            //moveNode(k,x,y);
            //BTreeDelete(k,y);
        }
        else{
            mergeNode(y,z,x,k);
        }



    }
    else{ //n� � folha

    }

}*/


/*int busca(int k)
{
    int idx=0;
    while (idx<n && keys[idx] < k)
        ++idx;
    return idx;
}*/
