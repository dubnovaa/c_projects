#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  s21_size_t counter = 0;
  int difference = 0;
  while (str1 && str2 && counter++ < n) {
    if (*str1 != *str2) {
      difference = *str1 - *str2;
      break;
    }
    str1++;
    str2++;
  }
  return difference;
}

// for (s21_size_t i = 0; *str1 && *str1 == *str2 && i < n; str1++, str2++, i++)
// {} return (int) (*str1 - *str2);