#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int null_ptr = 0;
  if (dst) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;

    if (src >= 0) {
      dst->bits[0] = src;
    } else {
      dst->bits[0] = -src;
      dst->bits[3] |= (1 << 31);
    }
  } else {
    null_ptr = 1;
  }
  return null_ptr;
}