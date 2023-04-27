#include "s21_string.h"

void *s21_memmove(void *dst, const void *src, s21_size_t count) {
  const char *tmp_src = src;
  char *tmp_dest = dst;
  if ((uintptr_t)src < (uintptr_t)dst &&
      (uintptr_t)src + count > (uintptr_t)dst) {
    // Copy from back to front
    while (count--) {
      *(tmp_dest + count) = *(tmp_src + count);
    }
  } else if ((uintptr_t)dst < (uintptr_t)src &&
             (uintptr_t)dst + count > (uintptr_t)src) {
    // Copy from front to back
    s21_size_t count_dest = 0;
    while (count_dest < count) {
      *(tmp_dest + count_dest) = *(tmp_src + count_dest);
      count_dest++;
    }
  } else {
    // They don't overlap for sure
    tmp_dest = s21_memcpy(dst, src, count);
  }
  return tmp_dest;
}