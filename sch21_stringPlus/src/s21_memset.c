#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  for (size_t i = 0; i < n; i++) {
    unsigned char copychar = (unsigned char)c;
    char *tmp = str;
    tmp[i] = copychar;
  }
  return str;
}