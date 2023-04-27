#include "s21_decimal.h"
#include "stdio.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;

  int rank1 = 0;
  result->bits[0] = 100;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = rank1 << 15;

  s21_decimal num1 = {{0, 0, 0, 0}}, num2 = {{0, 0, 0, 0}},
              num11 = {{0, 0, 0, 0}}, num21 = {{0, 0, 0, 0}};
  copy_decimal(value_1, &num1);
  copy_decimal(value_2, &num2);

  normalize_num(&num1);
  normalize_num(&num2);

  int digits_1 = read_digits(num1);
  int digits_2 = read_digits(num2);

  copy_decimal(num1, &num11);
  copy_decimal(num2, &num21);

  while (digits_1 < digits_2 || digits_1 > digits_2) {
    if (digits_1 < digits_2) {
      if (!mul_10(&num11)) {
        mul_10(&num1);
        write_digits(&num1, digits_1 + 1);
        digits_1++;
        copy_decimal(num1, &num11);
      } else {
        bin_div_10(&num2);
        write_digits(&num2, digits_2 - 1);
        digits_2--;
      }
    } else {
      if (!mul_10(&num21)) {
        mul_10(&num2);
        write_digits(&num2, digits_2 + 1);
        digits_2++;
        copy_decimal(num2, &num21);
      } else {
        bin_div_10(&num1);
        write_digits(&num1, digits_1 - 1);
        digits_1--;
      }
    }
    // printf("num1 ");
    // print(num1);
    // printf("num2 ");
    // print(num2);
  }

  int znak = 0;
  if (get_bit(num1, 127) == get_bit(num2, 127)) {
    error += bin_sum(num1, num2, &num1);
    znak = get_bit(value_1, 127);
  } else {
    write_bit(&num1, 127, 0);
    write_bit(&num2, 127, 0);
    if (s21_is_greater(num1, num2) == 1) {
      error += bin_sub(num1, num2, &num1);
      znak = get_bit(value_1, 127);
    } else {
      error += bin_sub(num2, num1, &num1);
      znak = get_bit(value_2, 127);
    }
  }

  // print(num1);
  write_bit(&num1, 127, znak);
  normalize_num(&num1);
  copy_decimal(num1, result);

  if (get_bit(*result, 127) == 1 && error > 0)
    error = 2;
  else if (error > 0)
    error = 1;

  if (error > 0) {
    result->bits[0] = 0;
    result->bits[1] = 0;
    result->bits[2] = 0;
    result->bits[3] = 0;
  }

  return error;
}

int mod_10(s21_decimal num) {
  int count = 0, znak = 1;
  for (int i = 0; i < MAX_BIT / 2; i++) {
    znak = -1 * ((i % 2 * 2) - 1);
    count += znak * (get_bit(num, i * 2) + get_bit(num, i * 2 + 1) * 2);
  }
  if (get_bit(num, 0) == 1) count = 1;
  return (count % 5 == 0) ? 1 : 0;
}

void normalize_num(s21_decimal *num) {
  unsigned int digits = read_digits(*num);
  while (digits > 0 && mod_10(*num)) {
    bin_div_10(num);
    write_digits(num, digits - 1);
    digits = read_digits(*num);
  }
}
