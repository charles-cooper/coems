// reverse a linked list

struct List {
  struct List *next;
  int data;
};
typedef struct List list_t;

void *null = 0; // no includes!
list_t *reverse(list_t *list) {
  list_t *next = list->next;
  list->next = null; // new end of the linked list.

  // one by one, flip the next pointer to the previous item.
  while (next) {
    list_t *tmp = next->next; // save forward
    next->next = list;        // flip backwards to backwards
    list = next;              // save current location so we can return it
    next = tmp;               // advance forward
  }
  return list;
}

// demo
#include <stdio.h>
#include <stdlib.h>
void print_list(list_t *list) {
  printf("[");
  while (list) {
    printf("%d", list->data);
    if (list->next) {
      printf(",");
    }
    list = list->next;
  }
  printf("]\n");
}
list_t *mklist(int *array, int len) {
  list_t *list = malloc(sizeof(list_t));
  list_t *ret = list;
  list->data = array[0];
  for (int i = 1; i < len; i++) {
    list_t *l = malloc(sizeof(list_t));
    l->data = array[i];
    list->next = l;
    list = l;
  }
  return ret;
}
int main(void) {
  int arr[5] = {1,2,3,4,5};
  list_t *l = mklist(arr, 5);
  print_list(l);
  l = reverse(l);
  print_list(l);
}
