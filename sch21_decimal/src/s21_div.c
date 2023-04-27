#include "s21_decimal.h"

int is_dzero(s21_decimal num);
void re_write(s21_decimal num, s21_decimal *result);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  int i = 1;
  int count = 0;
  s21_decimal buff1 = {{0, 0, 0, 0}};
  s21_decimal buff2 = {{0, 0, 0, 0}};
  s21_decimal one = {{1, 0, 0, 0}};
  re_write(value_1, &buff1);
  re_write(value_2, &buff2);
  if (!is_dzero(value_2)) {
    while (s21_is_greater(buff1, one)) {
      i = 1;
      while (s21_is_greater(buff1, buff2)) {
        mul_10(&buff2);
        i *= 10;
      }
      while (s21_is_less(buff1, buff2)) {
        bin_div_10(&buff2);
        i /= 10;
      }

      int k = 0;
      while (s21_is_greater_or_equal(buff1, buff2)) {
        s21_sub(buff1, buff2, &buff1);
        k++;
      }
      i *= k;
      count += i;
      re_write(value_2, &buff2);
    }
  }
  s21_from_int_to_decimal(count, result);
  return is_dzero(value_2) ? 3 : error;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  return s21_div(value_1, value_2, result);
}

void re_write(s21_decimal num, s21_decimal *result) {
  copy_decimal(num, result);
  write_bit(result, 127, 0);
  normalize_num(result);
}

//     int error = 0;

//     s21_decimal buff;
//     copy_decimal(value_1, &buff);
//     if (get_bit(value_1, 127) == 0)
//     {
//         while (get_bit(buff, 127) == 0 && !is_dzero(buff))
//         {
//             s21_sub(buff, value_2, result);
//             copy_decimal(*result, &buff);
//         }
//     }
//     else if (get_bit(value_1, 127) == 1 && !is_dzero(buff))
//     {
//         while (get_bit(buff, 127) == 1)
//         {
//             s21_add(buff, value_2, result);
//             copy_decimal(*result, &buff);
//         }
//     }
//   return is_dzero(value_2) ? 3 : error;
// }

int is_dzero(s21_decimal num) {
  int res = 0;
  if ((num.bits[0] == 0) && (num.bits[1] == 0) && (num.bits[2] == 0)) res = 1;
  return res;
}
