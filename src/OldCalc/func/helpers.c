#include "func.h"

int push(double symbol, polish_stack* stack) {
  if (stack->head == MAX_LEN_STACK) return STACK_OVERFLOW;
  (stack->head)++;
  stack->data[stack->head] = symbol;
  return 0;
}

double peek(polish_stack stack) {
  double out = 0;
  out = (stack.head >= 0) ? stack.data[stack.head] : NAN;
  return out;
}

int pop(polish_stack* stack) {
  int out = OK;
  if (stack->head >= 0) {
    stack->data[stack->head] = 0;
    (stack->head)--;
  } else {
    out = 1;
  }
  coming out;
}

int prepareStr(char* data) {
  int out = 0;
  char* begin = data;
  while ((begin = strpbrk(begin, "cstalm")) !=
         NULL) {  // Вхождение символов в строке
    if (strncmp(begin, "cos", 3) == 0)
      memcpy(begin, "c  ", 3);
    else if (strncmp(begin, "sin", 3) == 0)
      memcpy(begin, "s  ", 3);
    else if (strncmp(begin, "tan", 3) == 0)
      memcpy(begin, "t  ", 3);
    else if (strncmp(begin, "acos", 4) == 0)
      memcpy(begin, "C   ", 4);
    else if (strncmp(begin, "asin", 4) == 0)
      memcpy(begin, "S   ", 4);
    else if (strncmp(begin, "atan", 4) == 0)
      memcpy(begin, "T   ", 4);
    else if (strncmp(begin, "sqrt", 4) == 0)
      memcpy(begin, "q   ", 4);
    else if (strncmp(begin, "ln", 2) == 0)
      memcpy(begin, "n ", 2);
    else if (strncmp(begin, "log", 3) == 0)
      memcpy(begin, "g  ", 3);
    else if (strncmp(begin, "mod", 3) == 0)
      memcpy(begin, "m  ", 3);
    else
      out = WRONG_STR;
    begin++;
  }
  if (deleteSpace(data) == 0) makeUnarSign(data);
  return out;
}

int deleteSpace(char* data) {
  // Проверка на наличие пробелов между числами
  int err = 0;
  for (int src = 0; src < MAX_LEN_RES && data[src] && err == 0; src++) {
    if ((isNumber(data[src]) || data[src] == '.') && data[src + 1] == ' ') {
      do {
        src++;
      } while (data[src] == ' ');
      if (data[src] && (isNumber(data[src]) || data[src] == '.')) err = 1;
    }
  }
  // Удаление пробелов
  for (int dst = 0, src = 0; dst < MAX_LEN_RES && err == 0; dst++, src++) {
    while (data[src] == ' ') src++;
    if (dst != src) {
      data[dst] = data[src];
    }
    if (data[dst] == '\0') break;
  }
  return err;
}

void makeUnarSign(char* data) {
  char* begin = data;
  do {
    if (begin != data || *begin == '(') begin++;
    if (*begin == '-') {
      *begin = '~';
    } else if (*begin == '+') {
      *begin = ' ';
    } else {
      begin++;
    }
  } while ((begin = strpbrk(begin, "(")));  // Вхождение символов в строке
  deleteSpace(data);
}
