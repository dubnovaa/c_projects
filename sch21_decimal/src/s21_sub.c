#include <stdio.h>

#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal value_c_2 = {{0, 0, 0, 0}};
  copy_decimal(value_2, &value_c_2);
  write_bit(&value_c_2, 127, !get_bit(value_2, 127));
  return s21_add(value_1, value_c_2, result);
}
