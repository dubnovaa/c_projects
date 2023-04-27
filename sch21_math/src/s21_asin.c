#include <stdio.h>

#include "s21_math.h"

// how to compare NaNs????

long double s21_asin(double x) {
  long double res;
  if (x <= 1 && x >= -1) {
    x = x / s21_sqrt(1 - x * x);
    res = s21_atan(x);
  } else {
    res = 0 / 0.0;
  }
  return res;
}