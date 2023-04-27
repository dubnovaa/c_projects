#include "s21_math.h"

long double s21_exp(double x) {
  long double S = 1;
  long double add = 1;
  long double i = 1;
  int flag = 0;

  if (x < 0) {
    x = s21_fabs(x);
    flag = 1;
  }

  while (s21_fabs(add) > S21_EPS) {
    add *= x / i;
    i++;
    S += add;
  }

  if (flag == 1) {
    S = (long double)1 / S;
  }

  double S2 = (double)S;
  S = (long double)S2;

  return S;
}
