#include <stdio.h>

#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int null_ptr = 0;
  if (result) {
    s21_decimal integer = {{0, 0, 0, 0}};

    // int r = 0;
    // integer.bits[0] = 0;
    // integer.bits[1] = 0;
    // integer.bits[2] = 0;
    // integer.bits[3] = r << 16;

    // printf("integer:");
    // print(integer);

    s21_truncate(value, &integer);
    // printf("truncate:");
    // print(value);
    // printf("=======>");
    // print(integer);

    int znak1 = get_bit(value, 127);
    if (znak1 == 1) {
      s21_negate(value, &value);
      s21_negate(integer, &integer);
    }
    s21_sub(value, integer, result);

    // printf("sub:");
    // printf("--------+");
    // print(*result);

    s21_decimal half = {{0, 0, 0, 0}};
    int rank5 = 1;
    half.bits[0] = 5;
    half.bits[1] = 0;
    half.bits[2] = 0;
    half.bits[3] = rank5 << 16;

    s21_decimal one = {{0, 0, 0, 0}};
    int rank1 = 0;
    one.bits[0] = 1;
    one.bits[1] = 0;
    one.bits[2] = 0;
    one.bits[3] = rank1 << 16;

    // printf("half:");
    // print(half);

    // printf("one:");
    // print(one);

    if (s21_is_greater(*result, half) == 1) {
      // printf("++++++++++++\n");
      // printf("integer: %d", integer.bits[3]);
      // print(integer);
      // printf("one: %d", one.bits[3]);
      // print(one);
      s21_add(integer, one, result);
      // print(*result);
    } else {
      // printf("~~~~~~~~~~~~\n");
      // s21_sub(integer,one,result);
      copy_decimal(integer, result);
    }
    if (znak1 == 1) {
      s21_negate(*result, result);
    }
  } else {
    null_ptr = 1;
  }

  return null_ptr;
}
