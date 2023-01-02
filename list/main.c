#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  struct node *next;
  struct node *prev;
  int data;
}node;

void add(node *S, int new_data){
  node *n;
  if (S == NULL) return;
  n = (node *)malloc(sizeof(node));
  if (n == NULL) return;
  n->next = S;
  n->prev = S->prev;
  n->data = new_data;
  S->prev->next = n;
  S->prev = n;
}

void remove_node(node *S, int v){
  node *n;
  if (S == NULL || S->next == S) return;
  n = S->next;
  while (n != S && n->data != v) n = n->next;
  if (n == S) return;
  n->prev->next = n->next;
  n->next->prev = n->prev;
  free(n);
}

void merge(node *S){
  if (S == NULL || S->next == S) return;
  add(S, 7);
  add(S, 7);
  add(S, 7);
}

void search(node *S, int v){
  node *n;
  if (S == NULL || S->next == S) return;
  n = S->next;
  while (n != S && n->data != v) n = n->next;
  if (n == S){
    printf("False\n");
    return;
  }
  printf("True\n");
}

void print(node *S){
  node *e;
  if (S == NULL || S->next == S){
    printf("[ ]\n");
    return;
  }
  e = S->next;
  printf("[");
  do{
    printf(" %d",e->data);
    e = e->next;
  } while (e != S);
  printf(" ]\n");
}

int main (int argc, char *argv[])
{
  node *S;
  S = (node *)malloc(sizeof(node));
  S->next = S;
  S->prev = S;
  print(S);
  add(S, 2);
  print(S);
  add(S, 3);
  print(S);
  remove_node(S, 2);
  print(S);
  merge(S);
  print(S);
  search(S, 7);
  return 0;
}
