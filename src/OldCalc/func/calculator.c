#include "./func.h"

int calculator(char* input, double x, char* output) {
  setlocale(LC_NUMERIC, "C");
  char polish_str[MAX_LEN_RES] = "";
  int flag = polish(input, polish_str);
  double out = 0;
  if (!flag) flag = calc(polish_str, x, &out);
  if (fabs(out) < 1e-15) out = 0;
  if (flag == DIV_ZERO) {
    strcpy(output, "Div zero");
  } else if (flag) {
    strcpy(output, "Wrong input");
  } else {
    sprintf(output, "%.7lf", out);
  }
  return flag;
}