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
