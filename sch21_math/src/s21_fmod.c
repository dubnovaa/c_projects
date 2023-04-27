#include "s21_math.h"

long double s21_fmod(double x, double y) {
  long double s;
  int k = 1;

  if (y == 0) {
    s = 0 / 0.0;
  } else {
    if (x < 0) {
      k = -1;
    }
    x = s21_fabs(x);
    y = s21_fabs(y);
    while (x >= y) {
      x = x - y;
    }
    s = x * k;
  }
  return s;
}