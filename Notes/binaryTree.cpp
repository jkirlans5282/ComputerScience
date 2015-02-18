#include <iostream>

using namespace std;
struct TreeNode{
    int key;
    TreeNode *parent;
    TreeNode *leftChild;
    TreeNode *rightChild;
};

//recursively print keys in the tree, in order
//This is the inorder_tree_walk algorithm on page 288 of your book
void printNodeKeys(TreeNode *root){
    if(root->leftChild!=NULL){
        printNodeKeys(root->leftChild);
    }
    cout<<root->key<<endl;
    if(root->rightChild!=NULL){
        printNodeKeys(root->rightChild);
    }

}

//methods for searching a tree and adding a node
void addNode(TreeNode *root, TreeNode *z){
    //assume we don't have an empty tree, which means that root isn't NULL
    TreeNode *y = NULL;
    TreeNode *x = root;
    while(x != NULL){
        y = x;
        if(z->key < x->key){
            x = x->leftChild;
        }else{
            x = x->rightChild;
        }
    }
    z->parent = y;
    if(z->key < y->key){
        y->leftChild = z;
    }else{
        y->rightChild = z;
    }
}

//search the binary tree, the recursive version.
//Your book, page 291, has a non-recursive version
TreeNode *treeSearch(TreeNode *x, int k){
    if(x == NULL){
        cout<<"value not found in tree"<<endl;
        return x;
    }else if(x->key == k){ //value found
        return x;
    }else{
        if(x->key > k){
            treeSearch(x->leftChild, k);
        }else{
            treeSearch(x->rightChild, k);
        }
    }
}

int main()
{
    TreeNode *root = new TreeNode;
    root->parent = NULL;
    root->key = 12;
    TreeNode *next = new TreeNode;
    next->key = 10;
    addNode(root, next);

    next = new TreeNode;
    next->key = 8;
    addNode(root, next);

    next = new TreeNode;
    next->key = 15;
    addNode(root, next);

    printNodeKeys(root);

    TreeNode *x = treeSearch(root, 15);
    //this print statement works for every node except the root
    cout<<x->key<<" parent key "<<x->parent->key<<endl;
    return 0;
}