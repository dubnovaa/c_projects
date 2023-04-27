#include <stdio.h>

#include "s21_math.h"

long double s21_atan(double x) {
  int sign = 0;
  int reciprocate = 0;
  int minimize_angl = 0;
  if (x < 0) {
    x *= -1;
    sign = 1;
  }
  if (x > 1) {
    x = 1.0 / (double)x;
    reciprocate = 1;
  }
  if (x > 2 - sqrt3) {
    x = (sqrt3 * x - 1.0) / (double)(sqrt3 + x);
    minimize_angl = 1;
  }
  long double atan = 0;
  long double add = 1;
  int add_sign = -1;
  long double pow_x = x;
  int i = 1;
  while (!(add < epsilon * epsilon && add > -1 * epsilon * epsilon)) {
    add_sign *= -1;
    add = add_sign * pow_x / (double)i;
    atan += add;
    pow_x *= x * x;
    i += 2;
  }
  if (minimize_angl) atan += pi_6;
  if (reciprocate) atan = pi_2 - atan;
  if (sign) atan *= -1;
  return atan;
}