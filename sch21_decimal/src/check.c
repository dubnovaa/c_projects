#include "s21_decimal.h"
#include "tests/tests.h"

int main() {
  // int power0 = 0;
  // int power1 = 1;
  // int power2 = 2;
  // // int power3 = 3;
  int no_failed = 0;
  // s21_decimal lesser = {{1000, 0, 0, 0}}; //100
  // lesser.bits[3] = power1 << 16;
  // s21_decimal lesser1 = {{10000, 0, 0, 0}}; //100
  // lesser1.bits[3] = power2 << 16;
  // int a, b;
  // s21_from_decimal_to_int(lesser, &a);
  // s21_from_decimal_to_int(lesser1, &b);
  // printf("%d %d\n", a, b);

  // printf("%d %d\n", digit1, digit2);
  no_failed += tests_dec();
  no_failed += test_dec_comp();

  // print_hi();
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
  // return 0;
}
