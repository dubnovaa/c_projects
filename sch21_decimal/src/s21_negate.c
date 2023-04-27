#include "s21_decimal.h"

// int mul_10(s21_decimal *num);

int s21_negate(s21_decimal value, s21_decimal *result) {
  int null_ptr = 0;
  if (result) {
    for (int i = 0; i < 4; i++) {
      result->bits[i] = value.bits[i];
    }
    result->bits[3] ^= (1 << 31);
  } else {
    null_ptr = 1;
  }
  return null_ptr;
}

// int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {

// }

// int mul_10(s21_decimal *num) {
//     int error = 0;
//     for (int i = 0; i < 3; i++) {
//         int buff = 0;
//         if (num->bits[i] > 2147483647 && i < 2) num->bits[i+1] += 1;
//         else if (num->bits[i] > 2147483647 && i == 2) error = 1;
//         num->bits[i] = num->bits[i] << 1;
//         buff = num->bits[i];
//         if (num->bits[i] > 2147483647 && i < 2) num->bits[i+1] += 1;
//         else if (num->bits[i] > 2147483647 && i == 2) error = 1;
//         num->bits[i] = num->bits[i] << 1;
//         if (num->bits[i] > 2147483647 && i < 2) num->bits[i+1] += 1;
//         else if (num->bits[i] > 2147483647 && i == 2) error = 1;
//         num->bits[i] = num->bits[i] << 1;
//         if (num->bits[i] > 2147483647 && i < 2 && buff > 2147483647)
//         num->bits[i+1] += 1; else if (num->bits[i] > 2147483647 && i == 2 &&
//         buff > 2147483647) error = 1; num->bits[i] = num->bits[i] + buff;
//     }
//     return error;
// }