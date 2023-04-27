#include "s21_math.h"

long double s21_pow(double base, double exp) {
  long double result = 1;
  long double exp1 = 0;
  long double exp2;
  long double copy_exp = s21_fabs(exp);

  if (base != 0 || exp == 0) {
    while (s21_fabs(copy_exp) >= 1) {
      copy_exp--;
      exp1++;
    }
    exp2 = copy_exp;

    if (exp < 0) {
      base = 1.0 / base;
    }

    for (int i = 0; i < exp1; i++) {
      result = result * base;
    }

    if (exp2 != 0) {
      result = result * s21_exp(exp2 * s21_log(base));
    }
  } else {
    if (exp > 0) {
      result = 0;
    } else {
      result = 1.0 / 0.0;
    }
  }

  return result;
}
