#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const char *tmp = str;
  s21_size_t i = 0;

  for (; *(tmp + i) != '\0' && i < (n - 1) && *(tmp + i) != c; ++i)
    ;

  return *(tmp + i) == c ? (char *)tmp + i : NULL;
}
