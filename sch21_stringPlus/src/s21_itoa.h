#include "s21_parse.h"
#include "s21_string.h"

void s21_swap(char *a, char *b);

int getbuffersizeint(p_arg parg, int strlen);

void reverse_string(char *str, int length);

char *s21_long_itoa(long int num, char *buffer, int base, p_arg parg);
char *s21_hex(long int num, char *buffer, int capitals, p_arg parg);

int int_len(long int num);
int unsigned_int_len(unsigned long int num);

char *handle_signed_integers(p_arg parg, va_list args);
char *handle_hexadecimal(p_arg parg, va_list args);
char *handle_octal(p_arg parg, va_list args);
char *handle_unsigned_integers(p_arg parg, va_list args);
void flags(char *buffer, int ind, int sign, p_arg parg, int not_zero);