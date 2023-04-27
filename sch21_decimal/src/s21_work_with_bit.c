#include "s21_decimal.h"

void move_bits_right(s21_decimal num, s21_decimal *result, int count) {
  for (int i = 0; i < 96 - count; i++)
    write_bit(result, i, get_bit(num, (i + count)));
  for (int i = MAX_BIT - count; i < MAX_BIT; i++) write_bit(result, i, 0);
}

void move_bits_left(s21_decimal num, s21_decimal *result, int count) {
  for (int i = MAX_BIT - 1; i > count - 1; i--)
    write_bit(result, i, get_bit(num, (i - count)));
  for (int i = count - 1; i > -1; i--) write_bit(result, i, 0);
}

int get_bit(s21_decimal num, int bit) {
  return ((1 << (bit % 32)) & num.bits[bit / 32]) > 0 ? 1 : 0;
}

void write_bit(s21_decimal *num, int bit, int var) {
  if (var == 1)
    num->bits[bit / 32] |= (1 << (bit % 32));
  else
    num->bits[bit / 32] &= ~(1 << (bit % 32));
}

void copy_decimal(s21_decimal num, s21_decimal *result) {
  for (int i = 0; i < BITS_NUM + 1; i++) result->bits[i] = num.bits[i];
}

int read_digits(s21_decimal num) { return (num.bits[BITS_NUM] << 1) >> 17; }

void write_digits(s21_decimal *result, int digits) {
  int znak = get_bit(*result, 127);
  result->bits[BITS_NUM] = digits * 65536;
  write_bit(result, 127, znak);
}
