#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int compare = 0;
  const char *ptr1 = str1;
  const char *ptr2 = str2;

  while (n--) {
    if (*ptr1++ != *ptr2++) {
      compare = ptr1[-1] - ptr2[-1];
      break;
    }
  }

  return compare;
}
