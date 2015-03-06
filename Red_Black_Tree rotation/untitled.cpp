void Rotate_Right(Tree *tree, TreeNode * node){
    TreeNode *x = node->left;
    node->left = x->right;
    if(x->right != NULL){
        x->right->parent = node;
    }
    x->parent = node->parent;
    if(node->parent ==NULL){
        tree->root = x;
    }
    else if(node == node->parent->left){
        node->parent->left = x;
    }
    else{
        node->parent->right = x;
    }
    x->right = node;
    node->parent = x;
}

void Rotate_Left(Tree *tree, TreeNode * node){
    TreeNode *x = node->right;
    node->right = x->left;
    if(x->left != NULL){
        x->left->parent = node;
    }
    x->parent = node->parent;
    if(node->parent ==NULL){
        tree->root = x;
    }
    else if(node == node->parent->right){
        node->parent->right = x;
    }
    else{
        node->parent->left = x;
    }
    x->left = node;
    node->parent = x;
}