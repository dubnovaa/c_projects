#include "s21_parse.h"
#include "s21_string.h"

int getbuffersizedouble(p_arg parg, int strlen);
char *s21_double_tostr(double num, char *buffer, p_arg parg);
int double_len(double num, int precision);
char *handle_doubles(p_arg parg, va_list args);
int count_e(double num);
void reverse_string(char *str, int length);
void itoa(int n, char arr[]);
double covnertDoubleToE(double num, int e_value);
int setEnotation(char *buffer, int num, int sign, int eType);