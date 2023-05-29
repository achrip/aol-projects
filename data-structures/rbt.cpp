#include <assert.h>
#include <cstdio>
#include <cstdlib>

enum Colors {BLACK, RED}; 

struct RBT {
    int key, value, height, bf; 
    RBT *left, *right, *parent; 
    Colors color; 
};

RBT *baseroot; 

RBT *node_init(int key, int value); 
RBT *node_insert(RBT *root, RBT *node); 
RBT *node_delete(int key); 
RBT *tree_rotate_left(RBT *node); 
RBT *tree_rotate_right(RBT *node); 
RBT *tree_rotation(RBT *node); 
RBT *tree_colorize(RBT *node); 
bool *node_search(int key); 
void tree_print(RBT *root); 

int main(void) {
    baseroot = node_insert(baseroot, node_init(12, 0)); 
    printf("%s", baseroot->color); 
    baseroot = node_insert(baseroot, node_init(1, 1)); 
    //root = node_insert(root, node_init(2, 2)); 
    //root = node_insert(root, node_init(10,3)); 

    tree_print(baseroot); 
    
    return 0; 
}

RBT *node_init(int key, int value) {
    RBT *r = (RBT*)malloc(sizeof(RBT)); 
    r->value = value; 
    r->key = key; 
    r->left = r->right = NULL; 
    r->parent = r; 
    r->color = RED; 

    return r; 
}

RBT *node_insert(RBT *root, RBT *node) {
    if (!root) return node; 

    // assert(root->parent != NULL); 
    if (node->key > root->key){
        root->right = node_insert(root->right, node); 
        root->right->parent = root; // maybe is equivalent to node->parent = root (?)g 
        assert(root == tree_rotation(root->right)); 
        return (root->right->color == RED && root->color == RED) ? tree_rotation(root->right) : root; 
    }
    else if (node->key < root->key) {
        root->left = node_insert(root->left, node); 
        root->left->parent = root; // maybe is equivalent to node->parent = root (?)g 
        assert(root == tree_rotation(root->left)); 
        return (root->left->color == RED && root->color == RED) ? tree_rotation(root->left) : root; 
    }
    return root; 
}

RBT *tree_rotation(RBT *node) {
    assert(node != NULL); 

    RBT *parent = node->parent; 
    RBT *grandparent = parent->parent; 
    if (grandparent == parent && parent->color == RED) {
        parent->color = BLACK; 
        return node; 
    } 

    RBT *uncle = (parent == grandparent->left) ? grandparent->left : grandparent->right; 
    if (uncle && uncle->color == RED) {
        uncle->color = parent->color = BLACK; 

        return tree_rotation(parent->parent); 
    } 
    else if (parent == grandparent->left) {
        
    }
    else {
        
    }

    return node; 
}

void tree_print(RBT *root) {
    if (!root) return ; 

    tree_print(root->left);
    printf("[key: %d, val: %d]--", root->key, root->value); 
    tree_print(root->right);
}

