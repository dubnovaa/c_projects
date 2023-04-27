#include "s21_string.h"

int divide_string(char ch, const char *delim) {
  int res = 0;
  int i = 0;
  for (; !res && *(delim + i) != '\0'; i++) {
    if (ch == *(delim + i)) {
      res = 1;
    }
  }
  return res;
}

char *s21_strtok(char *str, const char *delim) {
  static char *remaining_string;
  char *result_ptr = S21_NULL;
  if (!str) str = remaining_string;  // if string given was null
  // if (!remaining_string) result_ptr = NULL;  // if remaining string was null

  int flag_startstring = 1;
  int flag_notnullstring = 1;
  while (flag_startstring) {
    if (divide_string(*str, delim))
      str++;  // if delim is in the start of the string
    else if (*str == '\0') {
      result_ptr = S21_NULL;
      flag_startstring = 0;
      flag_notnullstring = 0;
    } else
      flag_startstring = 0;
  }
  if (flag_notnullstring) {
    int flag = 1;
    result_ptr = str;
    while (flag) {
      if (*str == '\0') {
        remaining_string = str;
        flag = 0;
      } else if (divide_string(*str, delim)) {
        *str = '\0';
        remaining_string = str + 1;
        flag = 0;
      }
      str++;
    }
  }
  return result_ptr;
}
