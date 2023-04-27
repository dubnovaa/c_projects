#include "s21_decimal.h"
#include "stdbool.h"
#include "stdio.h"

int bin_sum(s21_decimal num_1, s21_decimal num_2, s21_decimal *result) {
  int k = 0;
  for (int i = 0; i < MAX_BIT; i++) {
    bool bit_num_1 = get_bit(num_1, i);
    bool bit_num_2 = get_bit(num_2, i);

    if ((!bit_num_1 && bit_num_2) || (bit_num_1 && !bit_num_2)) {
      if (k == 1)
        write_bit(result, i, 0);
      else
        write_bit(result, i, 1);
    } else if (bit_num_1 && bit_num_2) {
      if (k == 1)
        write_bit(result, i, 1);
      else
        write_bit(result, i, 0);
      k = 1;
    } else if (k == 0)
      ;
    else {
      write_bit(result, i, 1);
      k = 0;
    }
  }
  return k;
}

int bin_sub(s21_decimal num_1, s21_decimal num_2, s21_decimal *result) {
  int k = 0;
  for (int i = 0; i < MAX_BIT; i++) {
    bool bit_num_1 = get_bit(num_1, i);
    bool bit_num_2 = get_bit(num_2, i);

    if (k == 0) {
      if (!bit_num_1 && bit_num_2) {
        write_bit(result, i, 1);
        k = 1;
      } else if (bit_num_1 && !bit_num_2)
        write_bit(result, i, 1);
      else
        write_bit(result, i, 0);
    } else {
      if (!bit_num_1 && !bit_num_2)
        write_bit(result, i, 1);
      else if (!bit_num_1 && bit_num_2)
        write_bit(result, i, 0);
      else if (bit_num_1 && !bit_num_2) {
        write_bit(result, i, 0);
        k = 0;
      } else
        write_bit(result, i, 1);
    }
  }
  return (k * 2);
}