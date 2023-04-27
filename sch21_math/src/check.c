#include "tests/check_func.h"

int main() {
  int no_failed = 0;

  no_failed |= test_math();

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
