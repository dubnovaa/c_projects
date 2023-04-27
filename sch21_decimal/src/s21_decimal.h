#ifndef SRC_DECIMAL_H_
#define SRC_DECIMAL_H_

#define MAX_INT 2147483647
#define MAX_UN_INT 4294967295
#define BITS_NUM 3
#define MAX_BIT BITS_NUM * 32

typedef struct {
  unsigned int bits[BITS_NUM + 1];
} s21_decimal;

typedef struct {
  unsigned int bits[2 * BITS_NUM + 1];
} s21_long_decimal;

enum { LOW, MID, HIGH };

void print2_helper(unsigned x);
void print2(unsigned x);
void print(s21_decimal dec);
int mul_2(s21_decimal *num);
int mul_10(s21_decimal *num);
int get_bit(s21_decimal num, int bit);
void write_bit(s21_decimal *num, int bit, int var);
int bin_sum(s21_decimal num_1, s21_decimal num_2, s21_decimal *result);
int bin_sub(s21_decimal num_1, s21_decimal num_2, s21_decimal *result);
int bin_div_10(s21_decimal *num);
void move_bits_right(s21_decimal num, s21_decimal *result, int count);
void move_bits_left(s21_decimal num, s21_decimal *result, int count);
void copy_decimal(s21_decimal num, s21_decimal *result);
void normalize_num(s21_decimal *num);
int read_digits(s21_decimal num);
void write_digits(s21_decimal *result, int digits);
int mod_10(s21_decimal num);
int bin_mul(s21_decimal num1, s21_decimal num2, s21_decimal *result);

void move_long_bits_left(s21_decimal num, s21_long_decimal *result, int count);
int get_long_bit(s21_long_decimal num, int bit);
void write_long_bit(s21_long_decimal *num, int bit, int var);
int bin_long_sum(s21_long_decimal num_1, s21_long_decimal num_2,
                 s21_long_decimal *result);
void long_to_decimal(s21_long_decimal num, s21_decimal *result, int digits);
int bin_long_sub(s21_long_decimal num_1, s21_long_decimal num_2,
                 s21_long_decimal *result);
int long_mul_10(s21_long_decimal *num);
int long_mul_2(s21_long_decimal *num);
int bin_long_div_10(s21_long_decimal *num);
void move_l_bits_left(s21_long_decimal num, s21_long_decimal *result,
                      int count);
void move_long_bits_right(s21_long_decimal num, s21_long_decimal *result,
                          int count);
void copy_long_decimal(s21_long_decimal num, s21_long_decimal *result);
// int read_long_digits(s21_long_decimal num);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif  // !SRC_DECIMAL_H_
