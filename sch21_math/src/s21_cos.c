#include <stdio.h>

#include "s21_math.h"

double use_symmetry_cos(double x, int* flag) {
  if (x > 90 && x <= 180) {
    x = 180 - x;
    *flag *= -1;
  } else if (x > 180 && x <= 270) {
    *flag *= -1;
    x = x - 180;
  } else if (x > 270 && x <= 360) {
    x = 360 - x;
  }
  return x;
}

double use_periodicity(double x) {
  int k = (int)x / 360;
  x = x - k * 360;
  return x;
}

long double s21_cos(double x) {
  // x is given in radians, transfer it to degrees
  x = (double)x * 180 / (double)pi;
  int sign = 1;
  if (x < 0) x *= -1;
  x = use_periodicity(x);
  if (x > 90) x = use_symmetry_cos(x, &sign);
  long double cos = 0;
  if (x > 45) {
    x = 90 - x;
    x = (double)x * pi / (double)180;
    cos = s21_sin(x);
  } else {
    long double add = 1;
    x = (double)x * pi / (double)180;
    int add_sign = -1;
    long double pow_x = 1;
    long long int factorial = 1;
    int i = 0;
    while (!(add < epsilon * epsilon && add > -1 * epsilon * epsilon)) {
      if (i != 0) factorial *= i;
      if (i % 2 == 0) {
        add_sign *= -1;
        add = add_sign * pow_x / (long double)factorial;
        cos += add;
      }
      pow_x *= x;
      i++;
    }
  }
  if (sign < 0) cos *= -1;
  return cos;
}
