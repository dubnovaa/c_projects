#include <stdio.h>

#include "s21_decimal.h"

void copy_long_decimal(s21_long_decimal num, s21_long_decimal *result) {
  for (int i = 0; i < 2 * BITS_NUM + 1; i++) result->bits[i] = num.bits[i];
}

void move_long_bits_right(s21_long_decimal num, s21_long_decimal *result,
                          int count) {
  for (int i = 0; i < 2 * MAX_BIT - 1 - count; i++)
    write_long_bit(result, i, get_long_bit(num, (i + count)));
  for (int i = 2 * MAX_BIT - 1 - count; i < MAX_BIT; i++)
    write_long_bit(result, i, 0);
}

void move_l_bits_left(s21_long_decimal num, s21_long_decimal *result,
                      int count) {
  for (int i = 2 * MAX_BIT - 1; i > count - 1; i--)
    write_long_bit(result, i, get_long_bit(num, (i - count)));
  for (int i = count - 1; i > -1; i--) write_long_bit(result, i, 0);
}

void move_long_bits_left(s21_decimal num, s21_long_decimal *result, int count) {
  for (int i = 2 * MAX_BIT - 1; i > count - 1; i--)
    write_long_bit(result, i, get_bit(num, (i - count)));
  for (int i = count - 1; i > -1; i--) write_long_bit(result, i, 0);
}

int get_long_bit(s21_long_decimal num, int bit) {
  return ((1 << (bit % 32)) & num.bits[bit / 32]) > 0 ? 1 : 0;
}

void write_long_bit(s21_long_decimal *num, int bit, int var) {
  if (var == 1)
    num->bits[bit / 32] |= (1 << (bit % 32));
  else
    num->bits[bit / 32] &= ~(1 << (bit % 32));
}

// int read_long_digits(s21_long_decimal num) { return (num.bits[2 * BITS_NUM -
// 1] << 1) >> 17; }

// void write_long_digits(s21_long_decimal *result, int digits) {
//   int znak = get_bit(*result, 127);
//   result->bits[BITS_NUM] = digits * 32768;
//   write_bit(result, 127, znak);
// }

int bin_long_sum(s21_long_decimal num_1, s21_long_decimal num_2,
                 s21_long_decimal *result) {
  int k = 0;
  for (int i = 0; i < MAX_BIT; i++) {
    int bit_num_1 = get_long_bit(num_1, i);
    int bit_num_2 = get_long_bit(num_2, i);

    if ((!bit_num_1 && bit_num_2) || (bit_num_1 && !bit_num_2)) {
      if (k == 1)
        write_long_bit(result, i, 0);
      else
        write_long_bit(result, i, 1);
    } else if (bit_num_1 && bit_num_2) {
      if (k == 1)
        write_long_bit(result, i, 1);
      else
        write_long_bit(result, i, 0);
      k = 1;
    } else if (k == 0)
      ;
    else {
      write_long_bit(result, i, 1);
      k = 0;
    }
  }
  return k;
}

void long_to_decimal(s21_long_decimal num, s21_decimal *result, int digits) {
  int flag = 0;

  for (int i = MAX_BIT * 2 - 1; i > MAX_BIT && flag == 0; i--) {
    if (get_long_bit(num, i) == 1 && flag == 0) {
      flag = 1;
    }
  }

  while (flag == 1) {
    bin_long_div_10(&num);
    digits -= 1;
    for (int i = MAX_BIT * 2 - 1; i > MAX_BIT && flag == 0; i--) {
      if (get_long_bit(num, i) == 1 && flag == 0) {
        flag = 1;
      }
    }
  }

  for (int i = MAX_BIT; i > -1; i--) {
    if (get_long_bit(num, i) == 1)
      write_bit(result, i, 1);
    else
      write_bit(result, i, 0);
  }
  write_digits(result, digits);
}

int bin_long_div_10(s21_long_decimal *num) {
  s21_long_decimal buff = {{0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal buff2 = {{0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal q = {{0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal r = {{0, 0, 0, 0, 0, 0, 0}};
  move_long_bits_right(*num, &buff, 1);
  move_long_bits_right(*num, &buff2, 2);
  copy_long_decimal(buff, &q);

  bin_long_sum(buff, buff2, &q);
  move_long_bits_right(q, &buff, 4);
  bin_long_sum(q, buff, &q);
  move_long_bits_right(q, &buff, 8);
  bin_long_sum(q, buff, &q);
  move_long_bits_right(q, &buff, 16);
  bin_long_sum(q, buff, &q);
  move_long_bits_right(q, &buff, 32);
  bin_long_sum(q, buff, &q);
  move_long_bits_right(q, &buff, 64);
  bin_long_sum(q, buff, &q);
  move_long_bits_right(q, &buff, 128);
  bin_long_sum(q, buff, &q);
  move_long_bits_right(q, &buff, 256);
  bin_long_sum(q, buff, &q);
  move_long_bits_right(q, &buff, 512);
  bin_long_sum(q, buff, &q);
  move_long_bits_right(q, &buff, 1024);
  bin_long_sum(q, buff, &q);
  move_long_bits_right(q, &buff, 2048);
  bin_long_sum(q, buff, &q);

  move_long_bits_right(q, &q, 3);
  copy_long_decimal(q, &buff);
  long_mul_10(&buff);
  move_long_bits_right(buff, &buff, 1);
  long_mul_2(&buff);
  bin_long_sub(*num, buff, &r);
  buff2.bits[0] = 1;
  buff2.bits[1] = 0;
  buff2.bits[2] = 0;
  buff2.bits[3] = 0;
  buff2.bits[4] = 0;
  buff2.bits[5] = 0;
  buff2.bits[6] = 0;
  if (r.bits[0] > 4 || r.bits[1] > 0 || r.bits[2] > 0 || r.bits[3] > 0 ||
      r.bits[4] > 0 || r.bits[5] > 0)
    bin_long_sum(buff2, q, &q);
  copy_long_decimal(q, num);
  // unsigned q, r;
  // q = (*n >> 1) + (*n >> 2);
  // q = q + (q >> 4);
  // q = q + (q >> 8);
  // q = q + (q >> 16);
  // q = q >> 3;
  // r = *n - (((q << 2) + q) << 1);
  // *n = q + (r > 9);
  return 0;
}

int long_mul_2(s21_long_decimal *num) {
  int error = 0;
  if (get_long_bit(*num, 2 * MAX_BIT - 1) == 1)
    error = 1;
  else
    move_l_bits_left(*num, num, 1);
  return error;
  // return bin_sum(*num, *num, num);
}

int long_mul_10(s21_long_decimal *num) {
  int error = long_mul_2(num);
  s21_long_decimal buff = {{0, 0, 0, 0, 0, 0, 0}};
  for (int i = 0; i < BITS_NUM; i++) {
    buff.bits[i] = num->bits[i];
  }
  error += long_mul_2(num);
  error += long_mul_2(num);
  error += bin_long_sum(*num, buff, num);

  return error ? 1 : 0;
}

int bin_long_sub(s21_long_decimal num_1, s21_long_decimal num_2,
                 s21_long_decimal *result) {
  int k = 0;
  for (int i = 0; i < MAX_BIT; i++) {
    int bit_num_1 = get_long_bit(num_1, i);
    int bit_num_2 = get_long_bit(num_2, i);

    if (k == 0) {
      if (!bit_num_1 && bit_num_2) {
        write_long_bit(result, i, 1);
        k = 1;
      } else if (bit_num_1 && !bit_num_2)
        write_long_bit(result, i, 1);
      else
        write_long_bit(result, i, 0);
    } else {
      if (!bit_num_1 && !bit_num_2)
        write_long_bit(result, i, 1);
      else if (!bit_num_1 && bit_num_2)
        write_long_bit(result, i, 0);
      else if (bit_num_1 && !bit_num_2) {
        write_long_bit(result, i, 0);
        k = 0;
      } else
        write_long_bit(result, i, 1);
    }
  }
  return (k * 2);
}
