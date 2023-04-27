#include <stdio.h>

#include "s21_math.h"
// does not work with cos->0

double use_symmetry_tan(double x, int* flag) {
  if (x > 90) {
    x = 180 - x;
    *flag *= -1;
  }
  return x;
}

double use_periodicity_tan(double x) {
  int k = (int)x / 180;
  x = x - k * 180;
  return x;
}

long double s21_tan(double x) {
  // x is given in radians, transfer it to degrees
  x = (double)x * 180 / (double)pi;
  int sign = 1;
  if (x < 0) {
    sign *= -1;
    x *= -1;
  }
  x = use_periodicity_tan(x);
  x = use_symmetry_tan(x, &sign);
  int reciprocal = 0;
  if (x > 45) {
    reciprocal = 1;
    x = 90 - x;
  }
  // int half_angle = 0;
  // if (x > 22.5) {
  //     half_angle = 1;
  //     x = x / (double)2;
  // }
  x = (double)x * pi / (double)180;
  // // use connection between tan(x) and tan(x/2)

  long double tan = (long double)s21_sin(x) / (long double)s21_cos(x);
  if (reciprocal) tan = 1 / (long double)tan;
  // if (half_angle) tan = 2*tan/(long double)(1 - tan*tan);
  if (sign < 0) tan *= -1;
  return tan;
}