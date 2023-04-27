#include <stdio.h>

#include "s21_decimal.h"
#include "stdbool.h"

void print2_helper(unsigned x) {
  bool isodd = x % 2;
  x /= 2;
  if (x) print2_helper(x);
  putchar('0' + isodd);
}

void print2(unsigned x) {
  printf("Decimal:%u\tBinary:", x);
  // if (x < 0) putchar('-');
  print2_helper(x);
  putchar('\n');
}

void print(s21_decimal dec) {
  unsigned long int num1 = dec.bits[0] + dec.bits[1] * (MAX_UN_INT + 1);
  // for (int i = 127; i >= 0; i--) {
  //   if ((i + 1) % 32 == 0) printf(" ");
  //   printf("%d", get_bit(dec, i));
  // }
  if (get_bit(dec, 127) == 1) {
    printf(" -%lu\n", num1);
  } else {
    printf(" %lu\n", num1);
  }
}
