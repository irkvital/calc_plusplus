#include "func.h"

int calc(char* data, double x, double* result) {
  int out = 0;
  char* begin = data;
  polish_stack stack = STACK_INIT;
  while (*begin && out == 0) {
    if (isNumber(*begin) || *begin == '.') {
      if (*begin == 'x') {
        push(x, &stack);
        begin += 2;
      } else {
        push(readNumber(&begin), &stack);
      }
    } else if (isOperator(*begin)) {
      out = calcOperator(begin, &stack);
      begin++;
    } else if (isFunc(*begin)) {
      out = calcFunc(begin, &stack);
      if (!out) setZeroInStack(&stack);
      begin++;
    } else {
      out = WRONG_STR;
    }
  }
  if (stack.head == 0 && !out) {
    *result = peek(stack);
  } else {
    *result = NAN;
    if (out != DIV_ZERO) out = WRONG_STR;
  }
  coming out;
}

void setZeroInStack(polish_stack* stack) {
  if (fabs(peek(*stack)) < 1e-15) {
    if (pop(stack) == 0) push(0, stack);
  }
}

double readNumber(char** begin) {
  char** end = begin;
  double out = strtod(
      *begin,
      end);  // Прокручивает строку до первого символа после считанного числа
  *begin = (begin != end) ? *end : (*begin + 1);
  if (**begin == ' ') (*begin)++;
  return out;
}

// +-*/^m~
int calcOperator(char* begin, polish_stack* stack) {
  int out = 0;
  switch (*begin) {
    case '+':
      out = calcAdd(stack);
      break;
    case '-':
      out = calcSub(stack);
      break;
    case '*':
      out = calcMul(stack);
      break;
    case '/':
      out = calcDiv(stack);
      break;
    case '^':
      out = calcExp(stack);
      break;
    case 'm':
      out = calcMod(stack);
      break;
    case '~':
      out = calcUnar(stack);
      break;
  }
  coming out;
}

int calcAdd(polish_stack* stack) {
  double tmp_1 = 0, tmp_2 = 0;
  int out = calcOperatorStackActions(&tmp_1, &tmp_2, stack);
  if (out == 0) push(tmp_1 + tmp_2, stack);
  coming out;
}

int calcSub(polish_stack* stack) {
  double tmp_1 = 0, tmp_2 = 0;
  int out = calcOperatorStackActions(&tmp_1, &tmp_2, stack);
  if (out == 0) push(tmp_1 - tmp_2, stack);
  coming out;
}

int calcMul(polish_stack* stack) {
  double tmp_1 = 0, tmp_2 = 0;
  int out = calcOperatorStackActions(&tmp_1, &tmp_2, stack);
  if (out == 0) push(tmp_1 * tmp_2, stack);
  coming out;
}

int calcDiv(polish_stack* stack) {
  double tmp_1 = 0, tmp_2 = 0;
  int out = calcOperatorStackActions(&tmp_1, &tmp_2, stack);
  if (out == 0 && tmp_2 != 0) {
    push(tmp_1 / tmp_2, stack);
  } else if (tmp_2 == 0) {
    out = DIV_ZERO;
  }
  coming out;
}

int calcExp(polish_stack* stack) {
  double tmp_1 = 0, tmp_2 = 0;
  int out = calcOperatorStackActions(&tmp_1, &tmp_2, stack);
  if (out == 0) push(pow(tmp_1, tmp_2), stack);
  coming out;
}

int calcMod(polish_stack* stack) {
  double tmp_1 = 0, tmp_2 = 0;
  int out = calcOperatorStackActions(&tmp_1, &tmp_2, stack);
  if (out == 0) push(fmod(tmp_1, tmp_2), stack);
  coming out;
}

int calcUnar(polish_stack* stack) {
  double tmp = 0;
  tmp = peek(*stack);
  int out = pop(stack);
  if (out == 0) push(tmp * -1, stack);
  coming out;
}

int calcOperatorStackActions(double* tmp_1, double* tmp_2,
                             polish_stack* stack) {
  *tmp_2 = peek(*stack);
  int out = pop(stack);
  *tmp_1 = peek(*stack);
  out += pop(stack);
  coming out;
}

// cstCSTqng
int calcFunc(char* begin, polish_stack* stack) {
  int out = 0;
  switch (*begin) {
    case 'c':
      out = calcCos(stack);
      break;
    case 's':
      out = calcSin(stack);
      break;
    case 't':
      out = calcTan(stack);
      break;
    case 'C':
      out = calcAcos(stack);
      break;
    case 'S':
      out = calcAsin(stack);
      break;
    case 'T':
      out = calcAtan(stack);
      break;
    case 'q':
      out = calcSqrt(stack);
      break;
    case 'n':
      out = calcLn(stack);
      break;
    case 'g':
      out = calcLg(stack);
      break;
  }
  coming out;
}

int calcCos(polish_stack* stack) {
  double tmp = 0;
  tmp = peek(*stack);
  int out = pop(stack);
  if (out == 0) push(cos(tmp), stack);
  coming out;
}

int calcSin(polish_stack* stack) {
  double tmp = 0;
  tmp = peek(*stack);
  int out = pop(stack);
  if (out == 0) push(sin(tmp), stack);
  coming out;
}

int calcTan(polish_stack* stack) {
  double tmp = 0;
  tmp = peek(*stack);
  int out = pop(stack);
  if (out == 0) push(tan(tmp), stack);
  coming out;
}

int calcAcos(polish_stack* stack) {
  double tmp = 0;
  tmp = peek(*stack);
  int out = pop(stack);
  if (out == 0) push(acos(tmp), stack);
  coming out;
}

int calcAsin(polish_stack* stack) {
  double tmp = 0;
  tmp = peek(*stack);
  int out = pop(stack);
  if (out == 0) push(asin(tmp), stack);
  coming out;
}

int calcAtan(polish_stack* stack) {
  double tmp = 0;
  tmp = peek(*stack);
  int out = pop(stack);
  if (out == 0) push(atan(tmp), stack);
  coming out;
}

int calcSqrt(polish_stack* stack) {
  double tmp = 0;
  tmp = peek(*stack);
  int out = pop(stack);
  if (out == 0) push(sqrt(tmp), stack);
  coming out;
}

int calcLn(polish_stack* stack) {
  double tmp = 0;
  tmp = peek(*stack);
  int out = pop(stack);
  if (out == 0) push(log(tmp), stack);
  coming out;
}

int calcLg(polish_stack* stack) {
  double tmp = 0;
  tmp = peek(*stack);
  int out = pop(stack);
  if (out == 0) push(log10(tmp), stack);
  coming out;
}