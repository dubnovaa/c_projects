#include "s21_string.h"

int s21_strcmp2(const char *string, const char *word) {
  int flag = 0;
  while (*string && *word) {
    if (*string != *word) break;
    string++;
    word++;
  }
  if (*word == '\0') flag = 1;
  return flag;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *res = S21_NULL;
  const char *tmp = haystack;
  while (*tmp != '\0') {
    if ((*tmp == *needle) && s21_strcmp2(tmp, needle)) {
      res = (char *)tmp;
      break;
    }
    tmp++;
  }
  return res;
}
