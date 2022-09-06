#ifndef POLISH_H
#define POLISH_H

#include <math.h>
#include <string.h>

#include "stack.h"

enum Token {
  COS = 'o',
  SIN = 'i',
  TAN = 'a',
  ACOS = 'c',
  ASIN = 's',
  ATAN = 't',
  SQRT = 'q',
  LN = 'n',
  LOG = 'g'
};

int handler_letter(char* str, stack* p_data);
type fanc(type a, char fun);
int is_numb(char a);
int is_letter(char a);
type calculation(char* str, char* value_x, int* err);
int val(int a);
void revers_polish(char* str, type* res, char* value_x);

#endif  // POLISH_H
