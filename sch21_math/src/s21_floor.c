#include "s21_math.h"

long double s21_floor(double x) {
  long double k;

  if (x >= 0 || x == (long int)x) {
    k = (long int)x;
  } else {
    k = (long int)x - 1;
  }

  return k;
}