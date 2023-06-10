#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAX_ITEM 3

struct _btree {
    int keyCount; 
    int key[MAX_ITEM]; 
    _btree *child[MAX_ITEM]; 
} *root = NULL; 

int main(void) {
    puts("hello, btree");       

    return 0; 
}