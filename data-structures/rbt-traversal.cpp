#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum Colors {BLACK, RED}; 

struct _rbt {
    int value; 
    Colors color; 
    _rbt *left, *right, *parent; 
} *root = NULL; 

_rbt *noda(int value) {
    _rbt *node = (_rbt*)malloc(sizeof(_rbt)); 
    node->value = value; 
    node->parent = node->left = node->right = NULL; 
    node->color = RED; 

    return node; 
}

void tree_rotate_right(_rbt *noda) {
    _rbt *pivot = noda->left; 
    _rbt *node = pivot->right; 

    //rotate the subtree
    pivot->right = noda; 
    noda->left = node; 

    //recolor the nodes
    noda->color = RED; 
    pivot->color = BLACK; 

    //re-assign parents
    pivot->parent = noda->parent; 
    noda->parent = pivot; 
    
    //re-connect parent 
    if (!pivot->parent) root = pivot; 
    else if (noda == pivot->parent->left) 
        pivot->parent->left = pivot; 
    else if (noda == pivot->parent->right) 
        pivot->parent->right = pivot; 
}

void tree_rotate_left(_rbt *noda) {
    _rbt *pivot = noda->right; 
    _rbt *node = pivot->left; 

    //rotate the subtree
    pivot->left = noda; 
    noda->right = node; 

    //recolor the nodes
    noda->color = RED; 
    pivot->color = BLACK; 
    
    //re-assign parents
    pivot->parent = noda->parent; 
    noda->parent = pivot; 

    //re-connect parent
    if (!pivot->parent) root = pivot; 
    else if (noda == pivot->parent->left) 
        pivot->parent->left = pivot; 
    else if (noda == pivot->parent->right) 
        pivot->parent->right = pivot; 
}

void rbt_insertionFixup(_rbt* node) {
    _rbt *parent = node->parent; 

    //node is root, root must be black
    if (parent == NULL) {
        node->color = BLACK; 
        return; 
    }

    //node is not root, check for violations
    if (node->color != parent->color) return; 

    //beyond this, we must be having violations
    _rbt *grandparent = parent->parent; 
    bool parentIsRight = grandparent->right == parent ? true : false; 
    bool nodeIsRight = parent->right == node ? true : false; 
    _rbt *uncle = parentIsRight ?  grandparent->left : grandparent->right; 

    //two choices: uncle exists or not
    if(uncle && uncle->color == RED) {
        uncle->color = parent->color = BLACK; 
        grandparent->color = RED; 

        rbt_insertionFixup(grandparent); 
    }

    //uncle does not exist, refer to RBT rule "NULL nodes are BLACK"
    else {
        // parent is right child of grandparent 
        if (parentIsRight) {
            //zig-zag tree case
            if (!nodeIsRight) tree_rotate_right(parent); 

            //straight subtree case
            tree_rotate_left(grandparent); 
        }

        //parent is left child of grandparent
        else {
            //zig-zag tree case 
            if (nodeIsRight) tree_rotate_left(parent); 

            //straight subtree case
            tree_rotate_right(grandparent); 
        }
    }
}

void rbt_insertion(int value) {
    //check if there is an existing tree 
    if (!root) root = noda(value); 
    else {
        _rbt *cur = root, *par; 
        _rbt *node = noda(value); 
        //find the empty (NULL) node
        while (cur) {
            par = cur; 
            if (value > cur->value) cur = cur->right; 
            else if (value < cur->value) cur = cur->left; 
            else {
                printf("Error: A node exists with the value of %d\n", value); 
                return; 
            }
        }

        //append the data to the last non-NULL node
        if (value > par->value) par->right = node; 
        else par->left = node; 

        //connect newest node to its parent
        node->parent = par; 

        //post-insertion fixup
        rbt_insertionFixup(node);  
    }
    rbt_insertionFixup(root); 
}

void rbt_print(_rbt *root) {
    if (!root) return; 

    rbt_print(root->left); 
    printf("%d => ", root->value); 
    rbt_print(root->right); 
}

int height(_rbt *root) {
    if (!root) return 0; 

    int lH = height(root->left); 
    int rH = height(root->right); 

    if (lH > rH) return lH+1; 
    else return rH+1; 
}

void processCurrentLevel(_rbt *root, int l) {
    if (!root) return; 

    if (l == 0)
        printf("%d ", root->value); 
    else if (l > 0){
        processCurrentLevel(root->left, l-1); 
        processCurrentLevel(root->right, l-1); 
        puts(""); 
    }
}

void recursiveLevelOrder(_rbt *root) {
    int h = height(root); 
    for (int l = 0; l < h; l++) 
        processCurrentLevel(root, l); 
}



int main (void) {
    int arr[] = {41, 22, 5, 51, 48, 29, 18, 21, 45, 3} ; 

    for (int i = 0; i < 10; i++) rbt_insertion(arr[i]); 
    rbt_print(root); 

    return 0; 
}

