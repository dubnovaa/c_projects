#include <math.h>

#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int null_ptr = 0;
  s21_decimal buff = {{0, 0, 0, 0}};
  if (dst) {
    int minus = get_bit(src, 127);

    *dst = src.bits[0];
    int s = (src.bits[BITS_NUM] << 1) >> 17;
    *dst = *dst / (int)pow(10, s);

    if (minus == 1) {
      *dst = -*dst;
    }

    copy_decimal(src, &buff);
    // int d = read_digits(buff);
    // while (d > 0)
    // {
    //   d--;
    //   bin_div_10(&buff);
    // }
  } else {
    null_ptr = 1;
  }

  return buff.bits[1] > 0 || buff.bits[2] > 0 || null_ptr == 1 ? 1 : 0;
}
