#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  const char *tmp_src = src;
  char *tmp_dest = dest;
  s21_size_t i = 0;

  for (; *(tmp_src + i) != '\0' && i < n; i++) {
    tmp_dest[i] = tmp_src[i];
  }

  tmp_dest[i] = '\0';
  return tmp_dest;
}