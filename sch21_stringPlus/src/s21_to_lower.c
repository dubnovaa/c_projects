#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *ptr = S21_NULL;
  if (str) {
    ptr = malloc((s21_strlen(str) + 1) * sizeof(char));
    s21_strcpy(ptr, str);
    for (int j = 0; ptr[j] != '\0'; j++) {
      if (ptr[j] >= 65 && ptr[j] <= 90) ptr[j] += 32;
    }
  }
  return (void *)ptr;
}
