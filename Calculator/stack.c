#include "stack.h"

void init(stack* a) { a->count = 0; }

void push(stack* a, type value) {
  if (a->count < MAX_N) {
    a->data[a->count] = value;
    a->count++;
  } else {
    printf("error push!\n");
  }
}

type pop(stack* a) {
  type value = 0;
  if (a->count > 0) {
    a->count--;
    value = a->data[a->count];
  } else {
    printf("error pop!\n");
  }
  return value;
}

type pop_calc(stack* a, int* err) {
  type value = 0;
  if (a->count > 0) {
    a->count--;
    value = a->data[a->count];
  } else {
    printf("error pop!\n");
    *err = -1;
  }
  return value;
}

void cat_c(stack* a) {
  int i;
  i = a->count;  // i - количество элементов в стеке
  if (a->count == 0) return;  // стек пуст
  printf("2) ");
  do {
    i--;
    printf("%c ", (int)a->data[i]);
  } while (i > 0);
  printf("\n");
}

void cat_lf(stack* a) {
  int i;
  i = a->count;  // i - количество элементов в стеке
  if (a->count == 0) return;  // стек пуст
  // printf("2) ");
  do {
    i--;
    printf("res = %lf ", a->data[i]);
  } while (i > 0);
  printf("\n");
}

int empty(stack* a) {
  if (a->count == 0)
    return 1;
  else
    return 0;
}

type top(stack* a) {
  if ((a->count) > 0) {
    return a->data[a->count - 1];
  } else {
    return 0;
  }
}
