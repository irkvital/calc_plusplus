#ifndef FUNC_FUNC_H_
#define FUNC_FUNC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define coming return

#define ERR 1
#define MAX_LEN_RES 768
#define MAX_LEN_STACK 256

enum outs {
  OK = 0,
  MANY_DOTS = 1,
  STACK_OVERFLOW = 2,
  STACK_EMPTY = 3,
  MANY_SIGNS = 4,
  DIV_ZERO = 5,
  WRONG_BRACKETS = 6,
  WRONG_STR = 7,
};

typedef struct {
  double data[MAX_LEN_STACK];
  int head;
} polish_stack;

#define STACK_INIT \
  (polish_stack) { {0}, -1 }

typedef struct {
  int err;
  int x;
  int dot;
} polish_flags;

// На вход подается строка data[256], и строка result[768]. На выходе код
// возврата
int polish(char* data, char* result);
int calc(char* result, double x, double* out);
int calculator(char* input, double x, char* output);

// Заменяет в строке названия функций на уникальные идентификаторы этих функций
int prepareStr(char* data);
int deleteSpace(char* data);
// Находит и помечает в строке унарные знаки
void makeUnarSign(char* data);

// Операции со стэком

int push(double symbol, polish_stack* stack);
double peek(polish_stack stack);
int pop(polish_stack* stack);

// Вспомогательные для польской нотации

int isNumber(char symbol);
int isFunc(char symbol);
int isOperator(char symbol);
// 1, если первый оператор с большим или равным приоритетом
int operatorComparePriority(char a, char b);
int operatorSetPriority(char a);
void lexemNumber(char* data, int* src, char* result, int* dst,
                 polish_flags* flags);
void lexemFunc(char* data, int* src, polish_flags* flags, polish_stack* stack);
void lexemOperator(char* data, int* src, char* result, int* dst,
                   polish_stack* stack);
int lexemClose(char* result, int* dst, polish_flags* flags,
               polish_stack* stack);

// Вспомогательные функции для калькуляции

void setZeroInStack(polish_stack* stack);
double readNumber(char** begin);
int calcOperator(char* begin, polish_stack* stack);
int calcAdd(polish_stack* stack);
int calcSub(polish_stack* stack);
int calcMul(polish_stack* stack);
int calcDiv(polish_stack* stack);
int calcExp(polish_stack* stack);
int calcMod(polish_stack* stack);
int calcUnar(polish_stack* stack);
int calcOperatorStackActions(double* tmp_1, double* tmp_2, polish_stack* stack);
int calcFunc(char* begin, polish_stack* stack);
int calcCos(polish_stack* stack);
int calcSin(polish_stack* stack);
int calcTan(polish_stack* stack);
int calcAcos(polish_stack* stack);
int calcAsin(polish_stack* stack);
int calcAtan(polish_stack* stack);
int calcSqrt(polish_stack* stack);
int calcLn(polish_stack* stack);
int calcLg(polish_stack* stack);

#ifdef __cplusplus
}
#endif
#endif  // FUNC_FUNC_H_
