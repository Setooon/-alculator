#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 255

typedef double type;

typedef struct {
  type data[MAX_N];
  int count;
} stack;

void init(stack* a);
void push(stack* a, type value);
type pop_calc(stack* a, int* err);
type pop(stack* a);
int empty(stack* a);
type top(stack* a);

void cat_c(stack* a);
void cat_lf(stack* a);

#endif  // STACK_H
