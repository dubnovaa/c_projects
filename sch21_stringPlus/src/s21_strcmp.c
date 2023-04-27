#include "s21_string.h"

int s21_strcmp(const char *str1, const char *str2) {
  int res = 0;
  for (; *str1 && *str1 == *str2; str1++, str2++) continue;
  if (*str1 != *str2) {
    res = *str1 - *str2;
  }
  return res;
}
