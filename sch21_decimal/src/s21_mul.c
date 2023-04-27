#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  bin_mul(value_1, value_2, result);
  // write_digits(result, )
  return 0;
}

int bin_mul(s21_decimal num1, s21_decimal num2, s21_decimal *result) {
  s21_long_decimal buff1 = {{0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal buff2 = {{0, 0, 0, 0, 0, 0, 0}};

  for (int i = 0; i < BITS_NUM * 2 + 1; i++) {
    buff1.bits[i] = 0;
    buff2.bits[i] = 0;
  }

  for (int i = 0; i < MAX_BIT; i++) {
    if (get_bit(num2, i) == 1) {
      move_long_bits_left(num1, &buff1, i);
      bin_long_sum(buff1, buff2, &buff2);
    }
  }

  long_to_decimal(buff2, result, read_digits(num1) + read_digits(num2));
  if (get_bit(num1, 127) != get_bit(num2, 127)) write_bit(result, 127, 1);
  return read_digits(*result) > 0 ? 1 : 0;
}
