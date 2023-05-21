#include <assert.h>
#include <cstdio>
#include <cstdlib>

enum Colors {BLACK, RED}; 

struct RBT {
    int key, value, height, bf; 
    RBT *left, *right, *parent; 
    Colors color; 
} *root;

RBT *node_init(int key, int value); 
RBT *node_insert(RBT *node); 
RBT *node_delete(int key); 
RBT *tree_rotate_left(RBT *node); 
RBT *tree_rotate_right(RBT *node); 
RBT *tree_rotation(RBT *node); 
RBT *tree_colorize(RBT *node); 
bool *node_search(int key); 
int node_bf_set(RBT *node); 
int node_height_set(RBT *node); 
int node_height_get(RBT *node); 
int max (int a, int b); 

int main(void) {
    node_insert(node_init(12,0)); 
    node_insert(node_init(1,0)); 
    node_insert(node_init(2,0)); 

    return 0; 
}

RBT *node_init(int key, int value) {
    RBT *r = (RBT*)malloc(sizeof(RBT)); 
    r->value = value; 
    r->key = key; 
    r->left = r->right = r->parent = NULL; 
    r->color = RED; 

    return r; 
}

RBT *node_insert(RBT *node) {
    if (!root) return node; 

    //assert(root->parent != NULL); 
    if (node->key > root->key){
        root->right = node_insert(node); 
        root->right->parent = root; // maybe is equivalent to node->parent = root (?)g 
        assert(root == tree_rotation(root->right)); 
        return tree_rotation(root->right); 
    }
    else if (node->key < root->key) {
        root->left = node_insert(node); 
        root->left->parent = root; // maybe is equivalent to node->parent = root (?)g 
        assert(root == tree_rotation(root->left)); 
        return tree_rotation(root->left); 
    }
    else return root; 
}

RBT *tree_rotation(RBT *node) {
    assert(node == NULL); 
    if (node->color != node->parent->color) return node;

    RBT *gparent = node->parent->parent; 
    if (gparent->left->color == gparent->right->color) {
        // colorize the two
        return node->parent;
    }
    return node->parent; 
}

int node_height_set(RBT *node) {
    return node ? max(node_height_get(node->left), node_height_get(node->right)) + 1 : 0; 
}

int node_height_get(RBT *node) {
    return node ? node->height : 0; 
}

int node_bf_set(RBT *node) {
    return node ? node_height_get(node->left) - node_height_get(node->right) : 0; 
}

int max(int a, int b) {
    return a > b ? a : b; 
}