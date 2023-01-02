#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
  char* value;
  struct Node *left;
  struct Node *right;
}Node;

typedef struct BST{
  struct Node *root;
}BST;

void init_bst(BST *tree){
  if (tree == NULL){
    printf("error init_tree\n");
  }
  tree->root = malloc(sizeof(Node));
  if (tree->root == NULL){
    printf("error init_tree\n");
  }
}

int main (int argc, char *argv[])
{
  BST *tree;
  tree = malloc(sizeof(BST));
  init_bst(tree);
  free(tree);
  return 0;
}
