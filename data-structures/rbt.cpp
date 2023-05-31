#include <assert.h>
#include <cstdio>
#include <cstdlib>

enum Colors {BLACK, RED}; 

struct RBT {
    int key, value, height, bf; 
    RBT *left, *right, *parent; 
    Colors color; 
};

RBT *baseroot = NULL; 
RBT *node_init(int value); 
RBT *node_insert(RBT *root, RBT *node, RBT *parent); 
RBT *node_delete(int key); 
RBT *tree_rotate_left(RBT *node); 
RBT *tree_rotate_right(RBT *node); 
RBT *tree_rotation(RBT *node); 
RBT *tree_colorize(RBT *node); 
bool *node_search(int key); 
void tree_print(RBT *root); 

int main(void) {
    
    baseroot = node_insert(baseroot, node_init(12), baseroot); 
    baseroot = node_insert(baseroot, node_init(1), baseroot);
    RBT *rbt = node_init(10);
    baseroot = node_insert(baseroot, node_init(2), baseroot); 
    baseroot = node_insert(baseroot, node_init(19), baseroot); 
    baseroot = node_insert(baseroot, rbt, baseroot); 

    tree_print(baseroot); 
    
    return 0; 
}

RBT *node_init(int value) {
    RBT *r = (RBT*)malloc(sizeof(RBT)); 
    r->value = value; 
    r->left = r->right = NULL; 
    r->parent = r; 
    r->color = RED; 

    return r; 
}

RBT *node_insert(RBT *root, RBT *node, RBT *parent) {
    if (!root) {
        node->parent = parent; 
        return node; 
    }

    assert(root != NULL); 
    if (node->value > root->value){
        root->right = node_insert(root->right, node, root); 
        return tree_rotation(root->right); 
    }
    else if (node->value < root->value) {
        root->left = node_insert(root->left, node, root);
        return tree_rotation(root->left); 
    }
    return tree_rotation(root); 
}

RBT *tree_rotation(RBT *node) {
    assert(node != NULL); 


    RBT *parent = node->parent; 
    if (parent == NULL) {
        node->color = BLACK; 
        return node; 
    }

    if (parent->color == BLACK) return parent; 
    
    RBT *grandparent = parent->parent; 
    if (grandparent == NULL) {
        parent->color = BLACK; 
        return node; 
    } 

    RBT *uncle = (parent == grandparent->left) ? grandparent->right : grandparent->left; 
    if (uncle && uncle->color == RED) {
        uncle->color = parent->color = BLACK; 

        return parent; 
    } 
    // from here on uncle is BLACK 
    if (parent == grandparent->left) {
        if (node == parent->left) {
            //right rotation
            return tree_rotate_right(grandparent); 
        }
        else {
            //left-right rotation
            grandparent->left =tree_rotate_left(parent);
            return tree_rotate_right(grandparent); 
        }
    }
    else {
        if (node == parent->right) {
            //left rotation
            return tree_rotate_left(grandparent); 
        }
        else {
            //right-left rotation
            grandparent->right = tree_rotate_right(parent);
            return tree_rotate_left(grandparent);
        }
    }
}

RBT *tree_rotate_right(RBT *root) {
    RBT *pivot = root->left; 
    RBT *node = pivot->right; 

    pivot->right = root; 
    root->left = node; 
    pivot->parent = root->parent; 
    root->parent = pivot; 
    root->color = RED; 
    pivot->color = BLACK; 

    return pivot; 
}

RBT *tree_rotate_left(RBT *root) {
    RBT *pivot = root->right; 
    RBT *node = pivot->left; 

    pivot->left = root; 
    root->right = node; 
    pivot->parent = root->parent; 
    root->parent = pivot; 
    root->color = RED; 
    pivot->color = BLACK; 

    return pivot; 
}

void tree_print(RBT *root) {
    if (!root) return ; 

    tree_print(root->left);
    printf("%d -> ", root->value); 
    tree_print(root->right);
}

