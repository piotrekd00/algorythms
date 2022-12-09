#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MAX_VALUES = 100;
int MAX_LINE_LENGTH = 100;


typedef struct Node {
  char* data;
  struct Node *prev;
  struct Node *next;
} Node;


typedef struct List {
  Node *sentinel;
} List;


void init_list(List *list) {
  if (list == NULL) {
    printf("init_list Error");
    return;
  }

  list->sentinel = malloc(sizeof(Node));
  if (list->sentinel == NULL) {
    printf("init_list Error");
    return;
  }

  list->sentinel->prev = list->sentinel;
  list->sentinel->next = list->sentinel;
}

void print(List *list) {
  if (list == NULL || list->sentinel == NULL){
    printf("print Error\n");
    return;
  }
  printf("[");

  Node *curr_n = list->sentinel->next;

  while (curr_n != list->sentinel) {
    printf("%s", curr_n->data);
    if (curr_n->next != list->sentinel) {
      printf(" <-> ");
    }
    curr_n = curr_n->next;
  }

  printf("]\n");
}


void add_val(List *list, char* data) {
  if (list == NULL || list->sentinel == NULL) {
    printf("add Error");
    return;
  }

  Node *new_n = malloc(sizeof(Node));
  if (new_n == NULL) {
    printf("add Error");
    return;
  }

  new_n->data = malloc(strlen(data) + 1);
  if (new_n->data == NULL) {
    printf("add Error");
    free(new_n);
    return;
  }
  strcpy(new_n->data, data);
  new_n->prev = list->sentinel->prev;
  new_n->next = list->sentinel;

  list->sentinel->prev->next = new_n;
  list->sentinel->prev = new_n;
}


void delete_val(List *list, char* value) {
  if (list->sentinel == NULL){
    printf("remove Error\n");
    return;
  }
  int flag = 0;
  Node *curr_n = list->sentinel->next;
  Node *prev_n = list->sentinel;

  while (curr_n != list->sentinel) {
    if (strcmp(curr_n->data, value) == 0) {
      prev_n->next = curr_n->next;
      curr_n->next->prev = prev_n;
      free(curr_n->data);
      free(curr_n);
      flag = 1;
      curr_n = prev_n->next;
    } 
    else {
      prev_n = curr_n;
      curr_n = curr_n->next;
    }
  }
  if (flag == 0){
    printf("remove Error\n");
    return;
  }
}


void search_val(List *list, char* value) {
  if (list == NULL || list->sentinel == NULL){
    printf("search Error\n");
    return;
  }

  Node *curr_n = list->sentinel->next;

  while (curr_n != list->sentinel) {
    if (strcmp(curr_n->data, value) == 0) {
      printf("True\n");
      return;
    }
    curr_n = curr_n->next;
  }

  printf("False\n");
}


void non_repeated(List *list) {
  if (list == NULL || list->sentinel == NULL){
    printf("non_repeated Error\n");
    return;
  }

  Node *curr_n = list->sentinel->next;
  Node *prev_n = list->sentinel;
  char* values[MAX_VALUES];
  int num = 0;

  while (curr_n != list->sentinel) {
    int seen = 0;
    for (int i = 0; i < num; i++) {
      if (strcmp(curr_n->data, values[i]) == 0) {
        seen = 1;
        break;
      }
    }

    if (seen == 1) {
      prev_n->next = curr_n->next;
      curr_n->next->prev = prev_n;

      free(curr_n);
      curr_n = prev_n->next;
    } else {
      values[num++] = curr_n->data;
      prev_n = curr_n;
      curr_n = curr_n->next;
    }
  }
}


void merge(List *list) {
  if (list == NULL || list->sentinel == NULL){
    printf("merge Error\n");
    return;
  }
  add_val(list, "one");
  add_val(list, "two");
  add_val(list, "three");
}


void clean(List *list) {
  if (list == NULL || list->sentinel == NULL) {
    printf("clean Error\n");
    return;
  }

  Node *curr = list->sentinel->next;
  Node *next;

  while (curr != list->sentinel) {
    next = curr->next;
    free(curr->data);
    free(curr);
    curr = next;
  }

  free(list->sentinel);
  list->sentinel = NULL;
}


int main (int argc, char *argv[])
{
  List *L;
  L = (List *)malloc(sizeof(List));
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

    char *option = strtok(lines[j], " ");
    char *value = strtok(NULL, " ");

    if (strcmp(option, "init_list")==0){
      init_list(L);
    }
    else if (strcmp(option, "add")==0){
      add_val(L, value);
    }
    else if (strcmp(option, "print")==0){
      print(L);
    }
    else if (strcmp(option, "search")==0){
      search_val(L, value);
    }
    else if (strcmp(option, "remove")==0){
      delete_val(L, value);
    }
    else if (strcmp(option, "clean")==0){
      clean(L);
    }
    else if (strcmp(option, "non_repeated")==0){
      non_repeated(L);
    }
    else if (strcmp(option, "merge")==0){
      merge(L);
    }
    free(lines[j]);
  }
  if(L != NULL && L->sentinel != NULL){
    clean(L);
  }
  free(L);
  return 0;
}
