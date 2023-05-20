#include <cstdlib>
#include <cstring>
#include <cstdio>

struct Tree {
    int value, height, bf; 
    Tree *left, *right; 
}; 

Tree *construct(int value) {
    Tree *t = (Tree*) malloc (sizeof(Tree)); 
    t->value = value; 
    t->height = 1; 
    t->bf = 0; 
    t->left = t->right = NULL; 
    
    return t; 
}

int max(int a, int b) {
    return a > b ? a : b;
}

int getHeight(Tree *root) {
    return root ? root->height : 0;
}

int setHeight(Tree *root) {
    return root ? max(getHeight(root->left), getHeight(root->right)) + 1 : 0; 
}

int setBalanceFactor(Tree *root) {
    return root ? getHeight(root->left) - getHeight(root->right) : 0;
}

Tree *modify(Tree *root) {
    root->height = setHeight(root);
    root->bf = setBalanceFactor(root); 
    return root; 
}

Tree *leftRotation(Tree *root) {
    Tree *pivot = root->right; 
    Tree *child = pivot->left;
    pivot->left = root; 
    root->right = child; 
    root = modify(root); 
    pivot = modify(pivot); 

    return pivot; 
}

Tree *rightRotation(Tree *root) {
    Tree *pivot = root->left; 
    Tree *child = pivot->right;
    pivot->right = root; 
    root->left = child; 
    root = modify(root); 
    pivot = modify(pivot); 

    return pivot; 
}

Tree *rotate(Tree *root) {
    if (root->bf > 1) { 
        if (root->left->bf >= 0) 
            return rightRotation(root); 
        else {
            root->left = leftRotation(root->left); 
            return rightRotation(root);
        }
    }

    if (root->bf < -1) { 
        if (root->right->bf  <= 0) 
            return leftRotation(root); 
        else {
            root->right= rightRotation(root->right); 
            return leftRotation(root);
        }
    }
    return root; 
}

bool search(Tree *root, int value) {
    if (root) {
        if (root->value == value) 
            return true; 
        else if (value < root->value) 
            return search(root->left, value);
        else if (value > root->value)
            return search(root->right, value); 
    }
    return false; 
}

Tree *insert(Tree *root, Tree *t) {
    if (!root) return t; 
    else if (t->value > root->value) 
        root->right = insert(root->right, t); 
    else if (t->value < root->value) 
        root->left = insert(root->left, t); 

    return rotate(modify(root)); 
}

Tree *predecessor(Tree *root) {
    Tree *t = root->left; 
    while (t->right) t = t->right; 
    return t; 
}

Tree *successor(Tree *root) {
    Tree *t = root->right; 
    while (t->left) t = t->left; 
    return t; 
}
Tree *remove(Tree *root, int value) {
    if (!root) return root; 
    else if (value > root->value) 
        root->right = remove(root->right, value); 
    else if (value < root->value) 
        root->left = remove(root->left, value); 
    else {
        if (!root->left || !root->right) {
            Tree *tr = root->left ? root->left : root->right; 
            root->left = root->right = NULL; 
            free(root); 
            root = NULL; 
            return tr; 
        }

        Tree *p = predecessor(root); 
        //Tree *p = successor(root); 
        root->value = p->value; 
        root->left = remove(root->left, p->value); 
        //root->right = remove(root->right, p->value); 
    }

    return rotate(modify(root)); 
}

void inOrder(Tree *root) {
    if (!root) return; 

    inOrder(root->left);
    printf("%d ", root->value); 
    inOrder(root->right);
}

void preOrder(Tree *root) {
    if (!root) return; 

    printf("%d ", root->value); 
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(Tree *root) {
    if (!root) return; 

    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->value); 
}

int main() {
    Tree *root = NULL; 
    int tobeInserted[] = {6, 27, 19, 11, 36, 14, 81, 63, 75}; 
    int tobeErased[] = {14, 75, 36, 19, 11}; 

    for (int i = 0; i < 9; ++i) 
        root = insert(root, construct(tobeInserted[i]));  
    for (int i = 0; i < 5; ++i) 
        root = remove(root, tobeErased[i]);  

    while (1) {
        puts("\n\n1. Insertion\n2. Deletion\n3. Traversal\n4. Exit"); 
        printf("Choose: "); 

        int opt, in; 
        scanf("%d", &opt); 
        getchar(); 

        switch (opt) {
            case 1: 
                printf("Insert: "); 
                scanf("%d", &in); 
                getchar(); 

                root = insert(root, construct(in)); 
                break; 
            case 2: 
                printf("Delete: "); 
                scanf("%d", &in); 
                getchar(); 

                if (search(root, in)) {
                    puts("Data Found"); 
                    root = remove(root, in); 
                    printf("Value %d was deleted\n", in); 
                } else
                    puts("Data Not Found"); 

                break; 
            case 3: 
                printf("Preorder: "); 
                preOrder(root);
                puts("");

                printf("InOrder: "); 
                inOrder(root);
                puts("");

                printf("Postorder: "); 
                postOrder(root);
                puts("");

                break; 
            case 4: 
                puts("Thank you"); 
                exit(0); 
                break; 
            default:  
                break; 
        }
    }
    return 0; 
}
