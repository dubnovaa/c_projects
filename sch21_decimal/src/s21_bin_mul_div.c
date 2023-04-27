#include <stdio.h>

#include "s21_decimal.h"
#include "stdbool.h"

int mul_2(s21_decimal *num) {
  int error = 0;
  if (get_bit(*num, MAX_BIT - 1) == 1)
    error = 1;
  else
    move_bits_left(*num, num, 1);
  return error;
  // return bin_sum(*num, *num, num);
}

int mul_10(s21_decimal *num) {
  int error = mul_2(num);
  s21_decimal buff = {{0, 0, 0, 0}};
  for (int i = 0; i < BITS_NUM; i++) {
    buff.bits[i] = num->bits[i];
  }
  error += mul_2(num);
  error += mul_2(num);
  error += bin_sum(*num, buff, num);

  return error ? 1 : 0;
}

int bin_div_10(s21_decimal *num) {
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
  if (r.bits[0] > 4 || r.bits[1] > 0 || r.bits[2] > 0) bin_sum(buff2, q, &q);
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

// int bin_mul(s21_decimal num1, s21_decimal num2, s21_decimal *result) {
//     s21_decimal buff;
//     bin_sub(*result, *result, result);
//     for (int i = 0; i < MAX_BIT; i++) {
//         if (get_bit(num2, i) == 1) {
//             move_bits_left(num1, &buff, i);
//             bin_sum(*result, buff, result);
//         }
//     }
//     return 0;
// }
