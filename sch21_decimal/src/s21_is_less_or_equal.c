#include <stdio.h>

#include "s21_decimal.h"

int s21_is_less_or_equal(s21_decimal dec1, s21_decimal dec2) {
  int r = 0;
  int res = 0;
  int error = 0;
  int flag_rav = 0;
  int flag_rav_o = 0;

  // int digit1 = (dec1.bits[BITS_NUM] << 1) >> 17;
  // int digit2 = (dec2.bits[BITS_NUM] << 1) >> 17;

  int digit1 = read_digits(dec1);
  int digit2 = read_digits(dec2);

  int znak1 = get_bit(dec1, 127);
  int znak2 = get_bit(dec2, 127);

  // printf("digit1 = %d   ",digit1);
  // printf("stepen1 = %d\n",stepen1);
  // printf("digit2 = %d   ",digit2);
  // printf("stepen2 = %d\n",stepen2);

  if (dec1.bits[0] == dec2.bits[0] && dec1.bits[1] == dec2.bits[1] &&
      dec1.bits[2] == dec2.bits[2] && znak1 == znak2) {
    if (digit1 >= digit2) {
      return 1;
    } else
      return 0;
  }

  if (digit1 > digit2) {
    r = digit1 - digit2;
    for (int i = 0; i < r; i++) {
      if (error == 0) {
        error = mul_10(&dec2);
        write_digits(&dec1, read_digits(dec1) + 1);
        // dec1.bits[3] += 65536;
      }
    }
  } else if (digit1 < digit2) {
    r = digit2 - digit1;
    for (int i = 0; i < r; i++) {
      if (error == 0) {
        error = mul_10(&dec1);
        write_digits(&dec2, read_digits(dec2) + 1);
        // dec2.bits[3] += 65536;
      }
    }
  }

  if (dec1.bits[0] == dec2.bits[0] && dec1.bits[1] == dec2.bits[1] &&
      dec1.bits[2] == dec2.bits[2] && dec1.bits[0] == 0 && dec1.bits[1] == 0 &&
      dec1.bits[2] == 0) {
    flag_rav_o = 1;
  } else if (znak1 == 0 && znak2 == 1) {
    res = 0;
  } else if (znak1 == 1 && znak2 == 0) {
    res = 1;
  } else {
    if (dec1.bits[2] > dec2.bits[2]) {
      res = 0;
    } else if (dec1.bits[2] < dec2.bits[2]) {
      res = 1;
    } else if (dec1.bits[2] == dec2.bits[2]) {
      if (dec1.bits[1] > dec2.bits[1]) {
        res = 0;
      } else if (dec1.bits[1] < dec2.bits[1]) {
        res = 1;
      } else if (dec1.bits[1] == dec2.bits[1]) {
        if (dec1.bits[0] > dec2.bits[0]) {
          res = 0;
        } else if (dec1.bits[0] < dec2.bits[0]) {
          res = 1;
        } else if (dec1.bits[0] == dec2.bits[0]) {
          res = 1;
          flag_rav = 1;
        }
      }
    }
  }

  if (znak1 == 1 && znak2 == 1 && flag_rav != 1 && flag_rav_o != 1) {
    if (res == 0) {
      res = 1;
    } else {
      res = 0;
    }
  }

  if (flag_rav_o == 1) {
    res = 1;
  }

  return res;
}
