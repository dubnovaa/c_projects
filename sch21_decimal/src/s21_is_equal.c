#include "s21_decimal.h"

int s21_is_equal(s21_decimal dec1, s21_decimal dec2) {
  int zero_flag = 0;

  // int digit1 = (dec1.bits[BITS_NUM] << 1) >> 17;
  // int digit2 = (dec2.bits[BITS_NUM] << 1) >> 17;

  int digit1 = read_digits(dec1);
  int digit2 = read_digits(dec2);

  int znak1 = get_bit(dec1, 127);
  int znak2 = get_bit(dec2, 127);

  // printf("Знак 1: %d\n",znak1);
  // printf("Знак 2: %d\n",znak2);

  // unsigned long int num1 = dec1.bits[0] + dec1.bits[1] * (MAX_UN_INT + 1);
  // printf("%lu\n", num1);

  // unsigned long int num2 = dec2.bits[0] + dec2.bits[1] * (MAX_UN_INT + 1);
  // printf("%lu\n", num2);

  int r = 0;
  int res = 0;
  int error = 0;

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

  if (dec1.bits[0] == 0 && dec1.bits[1] == 0 && dec1.bits[2] == 0 &&
      dec2.bits[0] == 0 && dec2.bits[1] == 0 && dec2.bits[2] == 0) {
    zero_flag = 1;
  }

  if (error == 0 &&
      ((dec1.bits[0] == dec2.bits[0] && dec1.bits[1] == dec2.bits[1] &&
        dec1.bits[2] == dec2.bits[2] && znak1 == znak2) ||
       zero_flag == 1)) {
    res = 1;
  }

  return res;
}
