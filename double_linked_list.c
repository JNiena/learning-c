#include <stdio.h>
#include <stdlib.h>

struct Node {
  struct Node *previous;
  struct Node *next;
  int data;
};

struct Node *list_init(int data);
struct Node *list_get_last_node(struct Node *list);
struct Node *list_get_first_node(struct Node *list);
struct Node *list_get_node(struct Node *list, unsigned int index);
int list_get_last(struct Node *list);
int list_get_first(struct Node *list);
int list_get(struct Node *list, unsigned int index);
int list_length(struct Node *list);
void list_add(struct Node *list, int data);
void list_remove(struct Node *list, unsigned int index);

int main(void) {
  struct Node *list = list_init(5);
  list_add(list, 4);
  list_add(list, 9);
  list_add(list, 1);
  list_add(list, 4);
  list_add(list, 12);

  printf("List Length Before: %d\n", list_length(list));
  for (int i = 0; i < list_length(list); i++) {
    printf("Element %d: %d\n", i, list_get(list, i));
  }
  puts("\n\n\n\n");
  list_remove(list, 3);
  printf("List Length After: %d\n", list_length(list));
  for (int i = 0; i < list_length(list); i++) {
    printf("Element %d: %d\n", i, list_get(list, i));
  }

  return 0;
}

struct Node *list_init(int data) {
  struct Node *list = malloc(sizeof(struct Node));
  list->next = NULL;
  list->previous = NULL;
  list->data = data;
  return list;
}

struct Node *list_get_last_node(struct Node *list) {
  if (list->next == NULL) {
    return list;
  }
  return list_get_last_node(list->next);
}

struct Node *list_get_first_node(struct Node *list) {
  return list;
}

struct Node *list_get_node(struct Node *list, unsigned int index) {
  struct Node *current = list;
  for (int i = 0; i < index; i++) {
    current = current->next;
  }
  return current;
}

int list_get_last(struct Node *list) { return list_get_last_node(list)->data; }

int list_get_first(struct Node *list) {
  return list_get_first_node(list)->data;
}

int list_get(struct Node *list, unsigned int index) {
  return list_get_node(list, index)->data;
}

int list_length(struct Node *list) {
  int length = 1;
  struct Node *current = list;
  while ((current = current->next) != NULL) {
    length++;
  }
  return length;
}

void list_add(struct Node *list, int data) {
  struct Node *last = list_get_last_node(list);
  struct Node *new = list_init(data);
  new->previous = last;
  last->next = new;
}

void list_remove(struct Node *list, unsigned int index) {
  struct Node *pop = list_get_node(list, index);
  pop->previous->next = pop->next;
  pop->next->previous = pop->previous;
  free(pop);
}
