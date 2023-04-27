#include "s21_math.h"

long double s21_log(double x) {
  double result = 0;
  double compare = 0;

  if (x < 0) {
    result = 0 / 0.0;
  } else if (x == 0) {
    result = -1 / 0.0;
  } else {
    for (int i = 0; i < 100; i++) {
      compare = result;
      result = compare + 2 * (x - s21_exp(compare)) / (x + s21_exp(compare));
    }
  }

  return (result);
}
