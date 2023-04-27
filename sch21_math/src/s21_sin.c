#include <stdio.h>

#include "s21_math.h"
double use_symmetry_sin(double x, int* flag) {
  if (x > 90 && x <= 180) {
    x = 180 - x;
  } else if (x > 180 && x <= 270) {
    *flag *= -1;
    x = x - 180;
  } else if (x > 270 && x <= 360) {
    *flag *= -1;
    x = 360 - x;
  }
  return x;
}

long double s21_sin(double x) {
  // x is given in radians, transfer it to degrees
  x = (double)x * 180 / (double)pi;
  int sign = 1;
  if (x < 0) {
    sign *= -1;
    x *= -1;
  }
  x = use_periodicity(x);
  if (x > 90) x = use_symmetry_sin(x, &sign);
  long double sin = 0;
  if (x > 45) {  // sin(x) = cos(90-x)
    x = 90 - x;
    x = (double)x * pi / (double)180;
    sin = s21_cos(x);
  } else {
    long double add = 1;
    x = (double)x * pi / (double)180;
    int add_sign = -1;
    long double pow_x = 1;
    long long int factorial = 1;
    int i = 1;
    while (!(add < epsilon * epsilon && add > -1 * epsilon * epsilon)) {
      pow_x *= x;
      factorial *= i;
      if (i % 2 != 0) {
        add_sign *= -1;
        add = add_sign * pow_x / (long double)factorial;
        sin += add;
      }
      i++;
    }
  }
  if (sign < 0) sin *= -1;
  return sin;
}
