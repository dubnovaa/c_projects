#include <math.h>
#include <stdio.h>

#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = 0;
  double buf = (double)src;
  if (dst == NULL) {
    error = 1;
  } else if (src >= 7.922816251e+29 || src <= -7.922816251e+29) {
    error = 1;
  } else {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    if (src < 0) {
      dst->bits[3] = 1 << 31;
      src *= -1;
      buf *= -1;
    }

    unsigned scale = 0;
    while (scale < 28 && (int)buf / (int)powl(2, 21) == 0) {
      buf *= 10;
      scale++;
    }
    buf = round(buf);

    dst->bits[0] = (int)buf;
    write_digits(dst, scale);
    // s21_set_degree(dst, scale);
  }
  return error;
}