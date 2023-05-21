#include <assert.h>
#include <cstdio>
#include <cstdlib>

enum Colors {BLACK, RED}; 

struct RBT {
    int key, value, height, bf; 
    RBT *left, *right, *parent; 
    Colors color; 
};

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
    RBT *root = NULL; 
    root = node_insert(root, node_init(12, 0)); 
    root = node_insert(root, node_init(1, 1)); 
    //root = node_insert(root, node_init(2, 2)); 
    //root = node_insert(root, node_init(10,3)); 

    tree_print(root); 
    
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

    assert(root->parent != NULL); 
    if (node->key > root->key){
        root->right = node_insert(root->right, node); 
        root->right->parent = root; // maybe is equivalent to node->parent = root (?)g 
        assert(root == tree_rotation(root->right)); 
        return tree_rotation(root->right); 
    }
    else if (node->key < root->key) {
        root->left = node_insert(root->left, node); 
        root->left->parent = root; // maybe is equivalent to node->parent = root (?)g 
        assert(root == tree_rotation(root->left)); 
        return tree_rotation(root->left); 
    }
    return root; 
}

RBT *tree_rotation(RBT *node) {
    assert(node != NULL); 
    if (node->color != node->parent->color) return node;

    RBT *gparent = node->parent->parent; 
    if (gparent->left->color == gparent->right->color) {
        // colorize the two
        return node->parent;
    }
    return node->parent; 
}

void tree_print(RBT *root) {
    if (!root) return ; 

    tree_print(root->left);
    printf("[key: %d, val: %d]--", root->key, root->value); 
    tree_print(root->right);
}

