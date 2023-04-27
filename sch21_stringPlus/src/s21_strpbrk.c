#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  while (*str1) {
    if (s21_strchr(str2, *str1)) {
      break;
    } else {
      str1++;
    }
  }
  return (char *)str1;
}
