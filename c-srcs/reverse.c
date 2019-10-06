// https://adriann.github.io/programming_problems.html
// Write function that reverses a list, preferably in place.

// pointer to list, length of list
void reverse(int *list, int len) {

  // swap two elements at a time, progressing towards middle of list.
  // we can stop at the middle (if the number of elements is odd,
  // the middle element does not need to physically be swapped with
  // itself - that would be idempotent).
  //
  // e.g.
  //    [ 1, 2, 3, 4 ]
  // -> [ _4_, 2, 3, _1_ ]
  // -> [ 4, _3_, _2_, 1 ]
  for (int i = 0; i < len / 2; i++) {
    int tmp = list[i];
    list[i] = list[len - i - 1];
    list[len - i - 1] = tmp;
  }

}

// demo.
#include <stdio.h>
int print_array(int *array, int len) {
  printf("[");
  for (int i = 0; i < len - 1; i++) {
    printf("%d,", array[i]);
  }
  if (len > 0) {
    printf("%d", array[len - 1]);
  }
  printf("]\n");
}
int main(void) {
  int even_sized_list[10] = {1,2,3,4,5,6,7,8,9,10};
  reverse(even_sized_list, 10);
  print_array(even_sized_list, 10);

  int odd_sized_list[9] = {1,2,3,4,5,6,7,8,9};
  reverse(odd_sized_list, 9);
  print_array(odd_sized_list, 9);

}
