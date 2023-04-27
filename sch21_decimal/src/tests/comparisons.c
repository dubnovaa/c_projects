#include "tests.h"

// int s21_is_less(s21_decimal, s21_decimal);
// int s21_is_less_or_equal(s21_decimal, s21_decimal);
// int s21_is_greater(s21_decimal, s21_decimal);
// int s21_is_greater_or_equal(s21_decimal, s21_decimal);
// int s21_is_equal(s21_decimal, s21_decimal);
// int s21_is_not_equal(s21_decimal, s21_decimal);

START_TEST(is_less){
    // s21_decimal lesser1, middle, neg_middle, biggest;
    int power0 = 0;
    int power1 = 1;
    int power2 = 2;
    int power3 = 3;

    s21_decimal lesser = {{100, 0, 0, 0}}; //100
    lesser.bits[3] = power0 << 16;
    s21_decimal lesser1 = {{10000, 0, 0, 0}}; //100
    lesser1.bits[3] = power2 << 16;
    s21_decimal middle = {{10000, 0, 0, 0}}; //1000
    middle.bits[3] = power1 << 16;
    s21_decimal neg_middle = {{10000, 0, 0, 0}}; //-1000
    neg_middle.bits[3] = power1 << 16;
    neg_middle.bits[3] |= (1 << 31);
    s21_decimal biggest = {{10000, 1, 0, 0}}; //10000 + max_int 
    biggest.bits[3] = power3 << 16;
    ck_assert_int_eq(s21_is_less(lesser, middle), 1);
    ck_assert_int_eq(s21_is_less(middle, biggest), 1);
    ck_assert_int_eq(s21_is_less(lesser, biggest), 1);
    ck_assert_int_eq(s21_is_less(neg_middle, lesser), 1);
    ck_assert_int_eq(s21_is_less(lesser, neg_middle), 0);
    ck_assert_int_eq(s21_is_less(neg_middle, neg_middle), 0);
    ck_assert_int_eq(s21_is_less(lesser, lesser1), 0); 
    
}
END_TEST

START_TEST(is_less_or_equal){
    // s21_decimal lesser, lesser1, middle, middle1, neg_middle, biggest;
    int power0 = 0;
    int power1 = 1;
    int power2 = 2;
    int power3 = 3;

    s21_decimal lesser = {{100, 0, 0, 0}}; //100
    lesser.bits[3] = power0 << 16;
    s21_decimal lesser1 = {{10000, 0, 0, 0}}; //100
    lesser1.bits[3] = power2 << 16;
    s21_decimal middle = {{10000, 0, 0, 0}}; //1000
    middle.bits[3] = power1 << 16;
    s21_decimal neg_middle = {{10000, 0, 0, 0}}; //-1000
    neg_middle.bits[3] = power1 << 16;
    neg_middle.bits[3] |= (1 << 31);
    s21_decimal biggest = {{10000, 1, 0, 0}}; //10000 + max_int 
    biggest.bits[3] = power3 << 16;
    s21_decimal middle1 = {{1000000, 0, 0, 0}}; //1000
    middle1.bits[3] = power3 << 16;
    ck_assert_int_eq(s21_is_less_or_equal(lesser, middle), 1);
    ck_assert_int_eq(s21_is_less_or_equal(middle, biggest), 1);
    ck_assert_int_eq(s21_is_less_or_equal(lesser, biggest), 1);
    ck_assert_int_eq(s21_is_less_or_equal(biggest, lesser), 0);
    ck_assert_int_eq(s21_is_less_or_equal(neg_middle, lesser), 1);
    ck_assert_int_eq(s21_is_less_or_equal(lesser, neg_middle), 0);
    ck_assert_int_eq(s21_is_less_or_equal(lesser, lesser1), 1);
    ck_assert_int_eq(s21_is_less_or_equal(middle, middle1), 1);
    
}
END_TEST


START_TEST(is_greater){
    // s21_decimal lesser, lesser1, middle, neg_middle, biggest;
    int power0 = 0;
    int power1 = 1;
    int power2 = 2;
    int power3 = 3;

    s21_decimal lesser = {{100, 0, 0, 0}}; //100
    lesser.bits[3] = power0 << 16;
    s21_decimal lesser1 = {{10000, 0, 0, 0}}; //100
    lesser1.bits[3] = power2 << 16;
    s21_decimal middle = {{10000, 0, 0, 0}}; //1000
    middle.bits[3] = power1 << 16;
    s21_decimal neg_middle = {{10000, 0, 0, 0}}; //-1000
    neg_middle.bits[3] = power1 << 16;
    neg_middle.bits[3] |= (1 << 31);
    s21_decimal biggest = {{10000, 1, 0, 0}}; //10000 + max_int 
    biggest.bits[3] = power3 << 16;
    
    ck_assert_int_eq(s21_is_greater(lesser, lesser1), 0);
    ck_assert_int_eq(s21_is_greater(lesser, middle), 0);
    ck_assert_int_eq(s21_is_greater(biggest, middle), 1);
    ck_assert_int_eq(s21_is_greater(lesser, biggest), 0);
    ck_assert_int_eq(s21_is_greater(neg_middle, lesser), 0);
    ck_assert_int_eq(s21_is_greater(lesser, neg_middle), 1);
}
END_TEST

START_TEST(is_greater_equal){
    // s21_decimal lesser, lesser1, middle, middle1, neg_middle, biggest;
    int power0 = 0;
    int power1 = 1;
    int power2 = 2;
    int power3 = 3;

    s21_decimal lesser = {{100, 0, 0, 0}}; //100
    lesser.bits[3] = power0 << 16;
    s21_decimal lesser1 = {{10000, 0, 0, 0}}; //100
    lesser1.bits[3] = power2 << 16;
    s21_decimal middle = {{10000, 0, 0, 0}}; //1000
    middle.bits[3] = power1 << 16;
    s21_decimal neg_middle = {{10000, 0, 0, 0}}; //-1000
    neg_middle.bits[3] = power1 << 16;
    neg_middle.bits[3] |= (1 << 31);
    s21_decimal biggest = {{10000, 1, 0, 0}}; //10000 + max_int 
    biggest.bits[3] = power3 << 16;
    s21_decimal middle1 = {{1000000, 0, 0, 0}}; //1000
    middle1.bits[3] = power3 << 16;
    ck_assert_int_eq(s21_is_greater_or_equal(lesser, lesser1), 1);
    ck_assert_int_eq(s21_is_greater_or_equal(middle, middle1), 1);
    ck_assert_int_eq(s21_is_greater_or_equal(lesser, middle), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(biggest, middle), 1);
    ck_assert_int_eq(s21_is_greater_or_equal(lesser, biggest), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(neg_middle, lesser), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(lesser, neg_middle), 1);
}
END_TEST

// START_TEST(test_equal) {
//   s21_decimal test_value_1 = {{0, 0, 0, 0}};
//   s21_decimal test_value_2 = {{0, 0, 0, 0}};
//   s21_from_int_to_decimal(0, &test_value_1);
//   s21_from_int_to_decimal(0, &test_value_2);
//   ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 1);
//   ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 0);

//   test_value_1.bits[SCALE] = 0;
//   test_value_2.bits[SCALE] = 0;
//   s21_from_int_to_decimal(711996, &test_value_1);
//   s21_from_int_to_decimal(701995, &test_value_2);
//   ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 0);

//   test_value_1.bits[SCALE] = 0;
//   test_value_2.bits[SCALE] = 0;
//   s21_from_int_to_decimal(19993, &test_value_1);
//   s21_from_int_to_decimal(-6739, &test_value_2);
//   ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 0);

//   test_value_1.bits[SCALE] = 0;
//   test_value_2.bits[SCALE] = 0;
//   s21_from_int_to_decimal(-9993, &test_value_1);
//   s21_from_int_to_decimal(-9993, &test_value_2);
//   ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 1);

//   test_value_1.bits[SCALE] = 0;
//   test_value_2.bits[SCALE] = 0;
//   s21_from_int_to_decimal(11881, &test_value_1);
//   s21_from_int_to_decimal(11881, &test_value_2);
//   ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);
//   ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);
// }
// END_TEST

Suite *s21_dec_comparison_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_comparison");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, is_greater);
  tcase_add_test(tc_core, is_greater_equal);
  tcase_add_test(tc_core, is_less);
  tcase_add_test(tc_core, is_less_or_equal);
//   tcase_add_test(tc_core, );
//   tcase_add_test(tc_core, );
//   tcase_add_test(tc_core, );
//   tcase_add_test(tc_core, );
//   tcase_add_test(tc_core, );
//   tcase_add_test(tc_core, );
//   tcase_add_test(tc_core, );
//   tcase_add_test(tc_core, );
  suite_add_tcase(s, tc_core);

  return s;
}

int test_dec_comp() {
  int no_failed = 0;

  Suite *s;
  SRunner *runner;

  s = s21_dec_comparison_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return no_failed;
}

int print_hi(){
    printf("HI");
    return 0;
}
