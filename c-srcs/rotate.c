// copyright Charles Cooper 2019 - MIT license
// https://adriann.github.io/programming_problems.html
// Write a function that rotates a list by k elements. For example
// [1,2,3,4,5,6] rotated by two becomes [3,4,5,6,1,2]. Try solving this
// without creating a copy of the list. How many swap or move operations
// do you need?

// pointer to the list, length of the list, number of elements to rotate.
// do it the naive way. k * len iterations.
void rotate(int *list, int len, int k) {

  for (int j = 0; j < k; j++) {

    // [ T, D, V ]
    // [ _, D, V ] <T to the side>
    // [ D, _, V ] <T to the side>
    // [ D, V, _ ] <T to the side>
    // [ D, V, T ]

    int tmp = list[0]; // T to the side
    int i;
    for (i = 0; i < len - 1; i++) {
      list[i] = list[i + 1]; // move over!
    }
    list[i] = tmp; // put T back in.
  }
}

// do it a faster way. only need len iterations.
// it's easy to see this if len and k are mutually prime.
// you just keep moving one item into the slot of the
// previous item until you get back to the beginning.
// if they are not mutually prime, you need to find all
// the common denominators, each of which represents
// a unique "path" through the list.
//
// for instance, with len=6 and k=4. the paths look like
// [ 1 _ 3 _ 2 _ ]
// [ _ 1 _ 3 _ 2 ]

// helper function to calculate gcd
int _gcd(int x, int y) {
  int tmp;
  while (y) {
    tmp = x;
    x = y;
    y = tmp % y;
  }
  return x;
}
// we will need a mod function (C % is remainder).
int mod(int a, int b) {
  int r = a % b;
  return r < 0 ? r + b : r;
}
// the code for this is almost identical to the previous,
// since it simplifies to the naive version in the case
// that k = 1.
void rotate_gcd(int *list, int len, int k) {
  int gcd = _gcd(len, k);

  // we start each round at 1 greater than the previous index
  // we started at.
  for (int j = 0; j < gcd; j++) {

    // move this round
    int tmp = list[j];
    // progress through the list using modular arithmetic.
    // everything is modulo len.
    // each step, we increase i by k.
    // we finish if the next step will take us back where we
    // started.
    // note that in C, % is not mod but remainder, so for negative
    // arguments we need to use our mod function.
    int i;
    for (i = j; i != mod(j - k, len); i = mod(i + k, len)) {
      list[i] = list[mod(i + k, len)];
    }
    list[i] = tmp;

  }
}

// EDIT: I discovered after the fact that this has been gone over in
// https://eli.thegreenplace.net/2008/08/29/space-efficient-list-rotation
// my first two solutions were identical to the first two presented in
// that article. I don't have much interest in the third solution.
// The fourth solution is great and is presented below.
void reverse(int *list, int len) {
  for (int i = 0; i < len / 2; i++) {
    int tmp = list[i];
    list[i] = list[len - i - 1];
    list[len - i - 1] = tmp;
  }
}
void rotate_reverse(int *list, int len, int k) {
  reverse(list, k);
  reverse(list + k, len - k);
  reverse(list, len);
}

#include "demo_util.h"
int main(void) {
  int list[6] = {1,2,3,4,5, 6};
  rotate(list, 6, 3);
  print_array(list, 6);

  rotate_gcd(list, 6, 2);
  print_array(list, 6);

  rotate_reverse(list, 6, 1);
  print_array(list, 6);
}
