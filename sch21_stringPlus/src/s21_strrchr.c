#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *ptr = S21_NULL;
  int len = s21_strlen(str);
  for (int i = len; i >= 0; i--) {
    if (c == str[i]) {
      ptr = (char *)(str + i);
      break;
    }
  }

  return ptr;
}
