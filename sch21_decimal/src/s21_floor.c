#include <stdio.h>

#include "s21_decimal.h"
int is_zero(s21_decimal num) {
  // printf("%u %u %u\n", num.bits[0], num.bits[1], num.bits[2]);
  int res = 0;
  if ((num.bits[0] == 0) && (num.bits[1] == 0) && (num.bits[2] == 0)) {
    // printf("miltipl: %d\n", num.bits[0] * num.bits[1] * num.bits[2]);
    res = 1;
  }
  return res;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int null_ptr = 0;
  if (result) {
    // printf(".........%u %u %u\n", result->bits[0], result->bits[1],
    // result->bits[2]);
    int minus = get_bit(value, 127);
    int stepen = read_digits(value);
    int zero = is_zero(value);
    s21_truncate(value, result);
    // print(*result);
    if (minus == 1 && stepen != 0 && !zero) {
      // printf("im here");
      result->bits[0] += 1;
    }

  } else {
    null_ptr = 1;
  }

  return null_ptr;
}
