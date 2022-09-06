#include "polish.h"

type fanc(type a, char fun) {
  type res;
  if (fun == COS) res = cos(a);
  if (fun == SIN) res = sin(a);
  if (fun == TAN) res = tan(a);
  if (fun == ACOS) res = acos(a);
  if (fun == ASIN) res = asin(a);
  if (fun == ATAN) res = atan(a);
  if (fun == SQRT) res = sqrt(a);
  if (fun == LN) res = log(a);
  if (fun == LOG) res = log10(a);
  return res;
}

int atoff(char* str, type* n1) {
  int ans = 0;
  type n2 = 0;
  while (is_numb(str[ans])) *n1 = *n1 * 10 + str[ans++] - '0';
  if (str[ans++] == '.') {
    ans += atoff(&str[ans], &n2);
    while ((int)n2 > 0) n2 /= 10;
    *n1 += n2;
  }
  return --ans;
}

int is_numb(char a) { return (a <= '9' && a >= '0'); }
int is_letter(char a) { return (a >= 'a' && a <= 'z'); }

int val(int a) {
  int res = -1;
  if (a == '-' || a == '+') res = 2;
  if (a == '*' || a == '/') res = 3;
  if (a == '^') res = 4;
  if (is_letter(a)) res = 5;
  if (a == '(') res = 6;
  return res;
}

int handler_letter(char* str, stack* p_data) {
  int i = 0;
  if (str[i] == 's') {
    if (str[i + 1] == 'q') {
      push(p_data, SQRT);
      i += 5;
    } else if (str[i + 1] == 'i') {
      push(p_data, SIN);
      i += 4;
    }
  } else if (str[i] == 'l') {
    if (str[i + 1] == 'n') {
      push(p_data, LN);
      i += 3;
    } else if (str[i + 1] == 'o') {
      push(p_data, LOG);
      i += 4;
    }
  } else if (str[i] == 'a') {
    if (str[i + 1] == 'c') {
      push(p_data, ACOS);
      i += 5;
    } else if (str[i + 1] == 's') {
      push(p_data, ASIN);
      i += 5;
    } else if (str[i + 1] == 't') {
      push(p_data, ATAN);
      i += 5;
    }
  } else if (str[i] == 'c') {
    push(p_data, COS);
    i += 4;
  } else if (str[i] == 't') {
    push(p_data, TAN);
    i += 4;
  }
  return i;
}

void revers_polish(char* str, type* res, char* value_x) {
  printf("%s\n", str);
  int err = 0;
  stack data;
  stack* p_data = &data;
  init(p_data);
  char data_out[MAX_N];
  int index_out = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    if (is_letter(str[i])) {
      i += handler_letter(&str[i], p_data);
      if (str[i] == 'x') {
        for (size_t j = 0; j < strlen(value_x); j++)
          data_out[index_out++] = value_x[j];
        i += 2;
      }
    }
    if (is_numb(str[i])) {
      while (is_numb(str[i])) {
        data_out[index_out++] = str[i++];
      }
      if (str[i++] == '.') {
        data_out[index_out++] = '.';
        while (is_numb(str[i])) data_out[index_out++] = str[i++];
      }
    }
    if (str[i] == '+' || str[i] == '-') {
      if ((is_numb(str[i + 1]) && str[i - 1] != '.') ||
          (is_numb(str[i - 1]) && str[i + 1] != '.')) {
        if (str[i] == '-') data_out[index_out++] = str[i];
        continue;
      }
      while ((val(str[i]) <= val(top(p_data))) && ((top(p_data)) != '('))
        data_out[index_out++] = pop(p_data);
      push(p_data, str[i]);
    }
    if (str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == '(') {
      if (val(str[i]) > val(top(p_data)) || ((top(p_data)) == '(')) {
        push(p_data, str[i]);
      } else {
        data_out[index_out++] = pop(p_data);
        push(p_data, str[i]);
      }
    }
    if (str[i] == ')') {
      while (top(p_data) != '(') data_out[index_out++] = pop(p_data);
      pop(p_data);
      continue;
    }
    if (str[i] != ' ' && i) data_out[index_out++] = ' ';
  }
  while (data.count != 0) {
    data_out[index_out++] = pop(p_data);
  }
  *res = calculation(data_out, value_x, &err);
  printf("final = %s\n", data_out);
  printf("err = %d\n", err);
  if (err != 0) str[0] = 'f';
}

type calculation(char* str, char* value_x, int* err) {
  stack data;
  stack* p_dara = &data;
  init(p_dara);
  type token = 0;
  type n1, n2;
  int sign = 1;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == '-' && (is_numb(str[i + 1]))) {
      sign = -sign;
      continue;
    }
    if (is_numb(str[i])) {
      i += atoff(&str[i], &token);
      push(p_dara, token * sign);
      token = 0, sign = 1;
    }
    if (str[i] == '-') {
      n2 = pop_calc(p_dara, err), n1 = pop_calc(p_dara, err);
      push(p_dara, (n1 - n2));
    }
    if (str[i] == '/') {
      n2 = pop_calc(p_dara, err), n1 = pop_calc(p_dara, err);
      push(p_dara, n1 / n2);
    }
    if (str[i] == '+')
      push(p_dara, pop_calc(p_dara, err) + pop_calc(p_dara, err));
    if (str[i] == '*')
      push(p_dara, pop_calc(p_dara, err) * pop_calc(p_dara, err));
    if (str[i] == '^')
      push(p_dara, pow(pop_calc(p_dara, err), pop_calc(p_dara, err)));
    if (is_letter(str[i])) push(p_dara, fanc(pop_calc(p_dara, err), str[i]));
    if (!err) break;
  }
  return (pop_calc(p_dara, err));
}
