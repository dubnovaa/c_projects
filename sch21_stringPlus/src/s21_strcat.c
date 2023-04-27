#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
  char *tmp = dest + s21_strlen(dest);
  while (*src != '\0') {
    *tmp++ = *src++;
  }
  *tmp = '\0';
  return dest;
}
