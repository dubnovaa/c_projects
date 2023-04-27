#include "s21_decimal.h"

int is_2zero(s21_decimal num);
int bin_tdiv_10(s21_decimal *num);

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int minus = get_bit(value, 127);

  int stepen = read_digits(value);

  for (int i = 0; i < stepen; i++) bin_tdiv_10(&value);
  // write_digits(&value, 0);
  // if (minus == 0 && is_2zero(value) == 0) value.bits[0]++;

  copy_decimal(value, result);
  // result->bits[0] = value.bits[0];
  // result->bits[1] = value.bits[1];
  // result->bits[2] = value.bits[2];
  result->bits[3] = 0;

  if (minus == 1) write_bit(result, 127, minus);

  return 0;
}

int bin_tdiv_10(s21_decimal *num) {
  int znak = get_bit(*num, 127);
  s21_decimal buff = {{0, 0, 0, 0}};
  s21_decimal buff2 = {{0, 0, 0, 0}};
  s21_decimal q = {{0, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};
  move_bits_right(*num, &buff, 1);
  move_bits_right(*num, &buff2, 2);
  copy_decimal(buff, &q);
  bin_sum(buff, buff2, &q);
  move_bits_right(q, &buff, 4);
  bin_sum(q, buff, &q);
  move_bits_right(q, &buff, 8);
  bin_sum(q, buff, &q);
  move_bits_right(q, &buff, 16);
  bin_sum(q, buff, &q);
  move_bits_right(q, &buff, 32);
  bin_sum(q, buff, &q);
  move_bits_right(q, &buff, 64);
  bin_sum(q, buff, &q);
  move_bits_right(q, &buff, 128);
  bin_sum(q, buff, &q);
  move_bits_right(q, &q, 3);
  copy_decimal(q, &buff);
  mul_10(&buff);
  move_bits_right(buff, &buff, 1);
  mul_2(&buff);
  bin_sub(*num, buff, &r);
  buff2.bits[0] = 1;
  buff2.bits[1] = 0;
  buff2.bits[2] = 0;
  buff2.bits[3] = 0;
  if (r.bits[0] > 9 || r.bits[1] > 0 || r.bits[2] > 0) bin_sum(buff2, q, &q);
  copy_decimal(q, num);
  // unsigned q, r;
  // q = (*n >> 1) + (*n >> 2);
  // q = q + (q >> 4);
  // q = q + (q >> 8);
  // q = q + (q >> 16);
  // q = q >> 3;
  // r = *n - (((q << 2) + q) << 1);
  // *n = q + (r > 9);
  write_bit(num, 127, znak);
  return 0;
}

// int is_2zero(s21_decimal num) {
//   // printf("%u %u %u\n", num.bits[0], num.bits[1], num.bits[2]);
//   int res = 0;
//   if ((num.bits[0] == 0) && (num.bits[1] == 0) && (num.bits[2] == 0)) {
//     // printf("miltipl: %d\n", num.bits[0] * num.bits[1] * num.bits[2]);
//     res = 1;
//   }
//   return res;
// }
