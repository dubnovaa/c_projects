#include "s21_string.h"

char *s21_strchr(const char *s, int c) {
  while (*s != c && *s != '\0') s++;
  if (*s == c)
    return (char *)s;
  else
    return S21_NULL;
}
