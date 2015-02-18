#include <iostream>

using namespace std;

//define a TreeNode
/*We will eventually build a tree class with treenodes in the class,
but for now, we'll start with just the nodes.*/
struct TreeNode{
    string name;
	TreeNode *leftChild;
	TreeNode *rightChild;
	TreeNode *parent;


};

//recursively print cities in the tree
void printCityNames(TreeNode *root){
    cout<<"city: "<<root->name<<endl;
    //we can print the parent, provided the node has one
    if(root->parent!=NULL)
        cout<<"  parent "<<root->parent->name<<endl;
    if(root->leftChild!=NULL)
        printCityNames(root->leftChild);
    if(root->rightChild!=NULL)
        printCityNames(root->rightChild);
}
int main()
{
    //building the city network from the lecture notes
    //Denver is the root
    TreeNode *root = new TreeNode;
    root->name = "Denver";
    root->parent = NULL;

    TreeNode *left = new TreeNode;
    left->name = "Las Vegas";
    left->parent = root;

    TreeNode *right = new TreeNode;
    right->name = "Chicago";
    right->parent = root;

    root->leftChild = left;
    root->rightChild = right;

    TreeNode *next = left;
    TreeNode *leftL = new TreeNode;
    left->leftChild = leftL;
    leftL->name = "Los Angeles";
    leftL->leftChild = NULL;
    leftL->rightChild = NULL;
    leftL->parent = next;

    TreeNode *leftR = new TreeNode;
    left->rightChild = leftR;
    leftR->name = "Dallas";
    leftR->leftChild = NULL;
    leftR->rightChild = NULL;
    leftR->parent = next;

    cout<<right->parent->name<<endl;
    cout<<right->parent->leftChild->name<<endl;

    printCityNames(root);

    return 0;
}