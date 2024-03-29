#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 100

typedef struct Node{
  int value;
  int count;
  struct Node *left;
  struct Node *right;
}Node;

typedef struct BST{
  struct Node *root;
  int count;
}BST;

void init(BST **tree){
  *tree = malloc(sizeof(BST));
  if (tree == NULL){
    printf("Error init_tree\n");
    return;
  }
  memset(*tree, 0, sizeof(BST));
  (*tree)->count = 0;
}

Node *new_node(int data){
  Node *n_node = malloc(sizeof(Node));
  if (n_node == NULL){
    printf("Error insert\n");
  }
  n_node->value = data;
  n_node->count = 1;
  n_node->left = NULL;
  n_node->right = NULL;
  return n_node;
}

void insert_node(BST *tree, Node **root, int data) {
  if (*root == NULL) {
      *root = new_node(data);
      tree->count++;
      return;
  }
  if (data == (*root)->value) {
      (*root)->count++;
      return;
  } else if (data <= (*root)->value) {
      insert_node(tree, &(*root)->left, data);
  } else {
      insert_node(tree, &(*root)->right, data);
  }
}



Node *successor(Node *node) {
  Node *current = node;
  while (current->left != NULL) {
      current = current->left;
  }
  return current;
}

Node *delete_node(BST *tree, Node *root, int data) {
  if (root == NULL){
    printf("Error delete\n");
    return root;
  }
  if (data < root->value) {
    root->left = delete_node(tree, root->left, data);
  } else if (data > root->value) {
    root->right = delete_node(tree, root->right, data);
  } else {
    if (root->count > 1){
      root->count--;
    } else {
      if (root->left == NULL) {
        Node *temp = root->right;
        free(root);
        tree->count--;
        return temp;
      } else if (root->right == NULL) {
        Node *temp = root->left;
        free(root);
        tree->count--;
        return temp;
      }
      Node *n_successor = successor(root->right);
      root->value = n_successor->value;
      root->count = n_successor->count;
      root->right = delete_node(tree, root->right, n_successor->value);
    }
  }
  return root;
}


void print_inorder(BST *tree, Node *root) {
  static int count = 0;
  if (root == NULL) return;
  print_inorder(tree, root->left);
  count++;
  printf("%d", root->value);
  if (root->count > 1) {
    printf(":%d", root->count);
  }
  if (count < tree->count) {
    printf(" ");
  } else {
    printf("\n");
    count = 0;
  }
  print_inorder(tree, root->right);
}


void print_preorder(BST *tree, Node *root) {
  static int count = 0;
  if (root == NULL) return;
  count++;
  printf("%d", root->value);
  if (root->count > 1) {
    printf(":%d", root->count);
  }
  if (count < tree->count) {
    printf(" ");
  } else {
    printf("\n");
    count = 0;
  }
  print_preorder(tree, root->left);
  print_preorder(tree, root->right);
}


void print_postorder(BST *tree, Node *root) {
  static int count = 0;
  if (root == NULL) return;
  print_postorder(tree, root->left);
  print_postorder(tree, root->right);
  count++;
  printf("%d", root->value);
  if (root->count > 1) {
    printf(":%d", root->count);
  }
  if (count < tree->count) {
    printf(" ");
  } else {
    printf("\n");
    count = 0;
  }
}


void search(Node *root, int data) {
  if (root==NULL) {
    printf("False\n");
    return;
  }
  else if (root->value == data) {
    printf("True\n");
    return;
  }
  if (data <= root->value) {
    search(root->left, data);
  } else {
    search(root->right, data);
  }
}

void cleanup(BST *tree, Node *root) {
  if (root == NULL) return;
  cleanup(tree, root->left);
  cleanup(tree, root->right);
  free(root);
}

int main (int argc, char *argv[])
{
  BST *tree = NULL;
  char *lines[MAX_LINE_LENGTH];
  char line[MAX_LINE_LENGTH];
  int i = 0;

  while (fgets(line, sizeof(line), stdin) != NULL) {
    lines[i] = malloc(strlen(line) + 1);
    strcpy(lines[i], line);
    i++;
  }

  for (int j = 0; j < i; j++) {
    lines[j][strcspn(lines[j], "\n")] = 0;
    int value;
    char *option = strtok(lines[j], " ");
    char *str_value = strtok(NULL, " ");
    if (str_value != 0){
      value = atoi(str_value);
    }
    if (strcmp(option, "init_tree")==0){
      init(&tree);
    }
    else if (strcmp(option, "insert")==0){
      if (tree != NULL){
        insert_node(tree, &tree->root, value);
      }
      else{
        printf("Error insert\n");
      }
    }
    else if (strcmp(option, "search")==0){
      if (tree != NULL){
        search(tree->root, value);
      }
      else{
        printf("Error search\n");
      }
    }
    else if (strcmp(option, "delete")==0){
      if (tree != NULL){
        delete_node(tree, tree->root, value);
      }
      else{
        printf("Error delete\n");
      }
    }
    else if (strcmp(option, "in_order")==0){
      if (tree != NULL){
        print_inorder(tree, tree->root);
      }
      else{
        printf("Error in_order\n");
      }
    }
    else if (strcmp(option, "pre_order")==0){
      if (tree != NULL){
        print_preorder(tree, tree->root);
      }
      else{
        printf("Error pre_order\n");
      }
    }
    else if (strcmp(option, "post_order")==0){
      if (tree != NULL){
        print_postorder(tree, tree->root);
      }
      else{
        printf("Error post_order\n");
      }
    }
    free(lines[j]);
  }
  if (tree != NULL){
    cleanup(tree, tree->root);
    free(tree);
  }
  return 0;
}
