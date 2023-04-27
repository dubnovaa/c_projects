#include <math.h>

#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int null_ptr = 0;
  s21_decimal buff = {{0, 0, 0, 0}};
  if (dst) {
    int minus = get_bit(src, 127);

    int num = src.bits[0];
    int s = (src.bits[BITS_NUM] << 1) >> 17;
    int int_num = num / pow(10, s);
    int float_num = num % (int)pow(10, s);
    *dst = int_num + float_num * pow(10, -s);

    if (minus == 1) {
      *dst = -*dst;
    }

    copy_decimal(src, &buff);

    int d = read_digits(buff);
    while (d > 0) {
      d--;
      bin_div_10(&buff);
    }
  } else {
    null_ptr = 1;
  }

  return buff.bits[1] > 0 || buff.bits[2] > 0 || null_ptr == 1 ? 1 : 0;
}
