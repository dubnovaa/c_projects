#include "check_func.h"

#include <math.h>
#include <stdio.h>

START_TEST(test_s21_abs) {
  ck_assert_int_eq(s21_abs(-5), abs(-5));
  ck_assert_int_eq(s21_abs(5), abs(5));
  ck_assert_int_eq(s21_abs(0), abs(0));
  ck_assert_int_eq(s21_abs(1), abs(1));
  ck_assert_int_eq(s21_abs(-1), abs(-1));
  ck_assert_int_eq(s21_abs(-6), abs(-6));
}
END_TEST

START_TEST(test_s21_acos) {
  ck_assert_double_eq(s21_acos(0), acos(0));
  ck_assert_double_eq(s21_acos(.123), acos(.123));
  ck_assert_double_eq(s21_acos(1), acos(1));
  ck_assert_double_eq(s21_acos(.123456789), acos(.123456789));
  ck_assert_double_eq(s21_acos(.123456789), acos(.123456789));
  ck_assert_float_nan(s21_acos(4));
  ck_assert_float_nan(s21_acos(5));
  ck_assert_float_nan(s21_acos(6));
  ck_assert_float_nan(s21_acos(7));
  ck_assert_float_nan(s21_acos(-4));
  ck_assert_float_nan(s21_acos(-5));
  ck_assert_float_nan(s21_acos(-6));
  ck_assert_float_nan(s21_acos(-7));
}
END_TEST

START_TEST(test_s21_asin) {
  ck_assert_double_eq(s21_asin(0), asin(0));
  ck_assert_double_eq(s21_asin(.123), asin(.123));
  ck_assert_double_eq(s21_asin(1), asin(1));
  ck_assert_double_eq(s21_asin(.123456789), asin(.123456789));
  ck_assert_float_nan(s21_asin(4));
  ck_assert_float_nan(s21_asin(5));
  ck_assert_float_nan(s21_asin(6));
  ck_assert_float_nan(s21_asin(7));
  ck_assert_float_nan(s21_asin(-4));
  ck_assert_float_nan(s21_asin(-5));
  ck_assert_float_nan(s21_asin(-6));
  ck_assert_float_nan(s21_asin(-7));
}
END_TEST

START_TEST(test_s21_atan) {
  ck_assert_double_eq(s21_atan(0), atan(0));
  ck_assert_double_eq(s21_atan(.123), atan(.123));
  ck_assert_double_eq(s21_atan(-.123), atan(-.123));
  ck_assert_double_eq(s21_atan(.123456789), atan(.123456789));
  ck_assert_double_eq(s21_atan(.987654321), atan(.987654321));
}
END_TEST

START_TEST(test_s21_ceil) {
  ck_assert_double_eq(s21_ceil(0), ceil(0));
  ck_assert_double_eq(s21_ceil(.123456789), ceil(.123456789));
  ck_assert_double_eq(s21_ceil(.00000000000000000000000001),
                      ceil(.00000000000000000000000001));
  ck_assert_double_eq(s21_ceil(0.5), ceil(0.5));
  ck_assert_double_eq(s21_ceil(-0), ceil(-0));
  ck_assert_double_eq(s21_ceil(-.123456789), ceil(-.123456789));
  ck_assert_double_eq(s21_ceil(-.00000000000000000000000001),
                      ceil(-.00000000000000000000000001));
  ck_assert_double_eq(s21_ceil(-0.5), ceil(-0.5));
  ck_assert_double_eq(s21_ceil(-4.63), ceil(-4.63));
  ck_assert_double_eq(s21_ceil(4), ceil(4));
  ck_assert_double_eq(s21_ceil(5), ceil(5));
  ck_assert_double_eq(s21_ceil(6), ceil(6));
  ck_assert_double_eq(s21_ceil(7), ceil(7));
  ck_assert_double_eq(s21_ceil(8), ceil(8));
  ck_assert_double_eq(s21_ceil(9), ceil(9));
}
END_TEST

START_TEST(test_s21_cos) {
  char str1[100];
  char str2[100];
  ck_assert_double_eq(s21_cos(0), cos(0));
  sprintf(str1, "%f", (double)s21_cos(0.123456789));
  sprintf(str2, "%f", (double)cos(0.123456789));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_cos(-.123456789));
  sprintf(str2, "%f", (double)cos(-.123456789));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_cos(100.123456789));
  sprintf(str2, "%f", (double)cos(100.123456789));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_cos(70.987654321));
  sprintf(str2, "%f", (double)cos(70.987654321));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_cos(200));
  sprintf(str2, "%f", (double)cos(200));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_cos(270));
  sprintf(str2, "%f", (double)cos(270));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_cos(270));
  sprintf(str2, "%f", (double)cos(270));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_cos(270));
  sprintf(str2, "%f", (double)cos(270));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_cos(3 / 2 * 3.14));
  sprintf(str2, "%f", (double)cos(3 / 2 * 3.14));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_cos(4.537));
  sprintf(str2, "%f", (double)cos(4.537));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s21_sin) {
  char str1[100];
  char str2[100];
  ck_assert_double_eq(s21_sin(0), sin(0));
  sprintf(str1, "%f", (double)s21_sin(0.123456789));
  sprintf(str2, "%f", (double)sin(0.123456789));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_sin(-.123456789));
  sprintf(str2, "%f", (double)sin(-.123456789));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_sin(100.123456789));
  sprintf(str2, "%f", (double)sin(100.123456789));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_sin(70.987654321));
  sprintf(str2, "%f", (double)sin(70.987654321));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_sin(200));
  sprintf(str2, "%f", (double)sin(200));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_sin(270));
  sprintf(str2, "%f", (double)sin(270));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_sin(270));
  sprintf(str2, "%f", (double)sin(270));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_sin(270));
  sprintf(str2, "%f", (double)sin(270));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_sin(3 / 2 * 3.14));
  sprintf(str2, "%f", (double)sin(3 / 2 * 3.14));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_sin(4.537));
  sprintf(str2, "%f", (double)sin(4.537));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s21_floor) {
  ck_assert_double_eq(s21_floor(0), floor(0));
  ck_assert_double_eq(s21_floor(.123456789), floor(.123456789));
  ck_assert_double_eq(s21_floor(.00000000000000000000000001),
                      floor(.00000000000000000000000001));
  ck_assert_double_eq(s21_floor(0.5), floor(0.5));
  ck_assert_double_eq(s21_floor(-0), floor(-0));
  ck_assert_double_eq(s21_floor(-.123456789), floor(-.123456789));
  ck_assert_double_eq(s21_floor(-.00000000000000000000000001),
                      floor(-.00000000000000000000000001));
  ck_assert_double_eq(s21_floor(-0.5), floor(-0.5));
  ck_assert_double_eq(s21_floor(-4.63), floor(-4.63));
  ck_assert_double_eq(s21_floor(4), floor(4));
  ck_assert_double_eq(s21_floor(5), floor(5));
  ck_assert_double_eq(s21_floor(6), floor(6));
  ck_assert_double_eq(s21_floor(7), floor(7));
  ck_assert_double_eq(s21_floor(8), floor(8));
  ck_assert_double_eq(s21_floor(9), floor(9));
  ck_assert_double_eq(s21_floor(-4), floor(-4));
  ck_assert_double_eq(s21_floor(-5), floor(-5));
  ck_assert_double_eq(s21_floor(-6), floor(-6));
  ck_assert_double_eq(s21_floor(-7), floor(-7));
  ck_assert_double_eq(s21_floor(-8), floor(-8));
  ck_assert_double_eq(s21_floor(-9), floor(-9));
}
END_TEST

START_TEST(test_s21_log) {
  ck_assert_ldouble_infinite(s21_log(0));
  ck_assert_ldouble_nan(s21_log(-5));
}
END_TEST

START_TEST(test_s21_fmod) {
  ck_assert_ldouble_nan(s21_fmod(0, 0));
  ck_assert_ldouble_eq(s21_fmod(0, 14), fmod(0, 14));
  ck_assert_ldouble_eq(s21_fmod(15, 14), fmod(15, 14));
  ck_assert_ldouble_eq(s21_fmod(-15, 14), fmod(-15, 14));
}
END_TEST

START_TEST(test_s21_pow) {
  ck_assert_ldouble_infinite(s21_pow(0, -10));
  ck_assert_ldouble_eq(s21_pow(1, 14), pow(1, 14));
  ck_assert_ldouble_eq(s21_pow(1, -0.5), pow(1, -0.5));
  ck_assert_ldouble_eq(s21_pow(1, 0), pow(1, 0));
}
END_TEST

START_TEST(test_s21_tan) {
  char str1[100];
  char str2[100];
  ck_assert_double_eq(s21_tan(0), tan(0));
  sprintf(str1, "%f", (double)s21_tan(0.123456789));
  sprintf(str2, "%f", (double)tan(0.123456789));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_tan(-.123456789));
  sprintf(str2, "%f", (double)tan(-.123456789));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_tan(100.123456789));
  sprintf(str2, "%f", (double)tan(100.123456789));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_tan(70.987654321));
  sprintf(str2, "%f", (double)tan(70.987654321));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_tan(200));
  sprintf(str2, "%f", (double)tan(200));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_tan(270));
  sprintf(str2, "%f", (double)tan(270));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_tan(270));
  sprintf(str2, "%f", (double)tan(270));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_tan(270));
  sprintf(str2, "%f", (double)tan(270));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_tan(3 / 2 * 3.14));
  sprintf(str2, "%f", (double)tan(3 / 2 * 3.14));
  ck_assert_str_eq(str1, str2);
  sprintf(str1, "%f", (double)s21_tan(4.537));
  sprintf(str2, "%f", (double)tan(4.537));
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite *s21_cs_string_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_math");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_abs);
  tcase_add_test(tc_core, test_s21_acos);
  tcase_add_test(tc_core, test_s21_asin);
  tcase_add_test(tc_core, test_s21_atan);
  tcase_add_test(tc_core, test_s21_ceil);
  tcase_add_test(tc_core, test_s21_cos);
  tcase_add_test(tc_core, test_s21_floor);
  tcase_add_test(tc_core, test_s21_sin);
  tcase_add_test(tc_core, test_s21_log);
  tcase_add_test(tc_core, test_s21_fmod);
  tcase_add_test(tc_core, test_s21_pow);
  tcase_add_test(tc_core, test_s21_tan);
  suite_add_tcase(s, tc_core);

  return s;
}

int test_math() {
  int no_failed = 0;

  Suite *s;
  SRunner *runner;

  s = s21_cs_string_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return no_failed;
}
