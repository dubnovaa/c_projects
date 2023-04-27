#include "s21_itoa.h"

#include "s21_parse.h"
#include "s21_string.h"

void s21_swap(char *a, char *b) {
  char buff = *a;
  *a = *b;
  *b = buff;
}

int getbuffersizeint(p_arg parg, int strlen) {
  int buffersize = 0;
  if (parg.precision >= parg.width && parg.precision >= strlen) {
    buffersize = parg.precision + 1;
  } else if (parg.width >= parg.precision && parg.width >= strlen) {
    buffersize = parg.width + 1;
  } else
    buffersize = strlen;
  return buffersize;
}

void reverse_string(char *str, int length) {
  int start = 0;
  int end = length - 1;
  while (start < end) {
    s21_swap(str + start, str + end);
    start++;
    end--;
  }
}

char *s21_long_itoa(long int num, char *buffer, int base, p_arg parg) {
  int ind = 0;
  int sign = 1;
  if (num == 0 && parg.precision != 0) {
    buffer[ind] = '0';
    ind++;
    buffer[ind] = '\0';
  }
  if (num < 0) {  // base == 10 &&
    sign = -1;
    num = num * (-1);
  }
  int rest;
  int not_zero = num != 0 ? 1 : 0;
  while (num != 0) {
    rest = num % base;
    if (rest > 9)
      buffer[ind++] = (rest - 10) + 'a';
    else
      buffer[ind++] = rest + '0';
    num = num / base;
    // printf("%s\n", buffer);
  }
  if (parg.flag_hashtag && not_zero) {
    if (base == 8) buffer[ind++] = '0';
  }  // printf("before flags |%s|\t", buffer);
  flags(buffer, ind, sign, parg, not_zero);
  // if (base == 8) printf("after flags |%s|\n", buffer);
  return buffer;
}

char *s21_unsigned_long_itoa(unsigned long int num, char *buffer, int base,
                             p_arg parg) {
  int ind = 0;
  if (num == 0) {
    buffer[ind] = '0';
    ind++;
    buffer[ind] = '\0';
  }
  int rest;
  while (num != 0) {
    rest = num % base;
    if (rest > 9)
      buffer[ind++] = (rest - 10) + 'a';
    else
      buffer[ind++] = rest + '0';
    num = num / base;
  }
  if (parg.flag_zero && !parg.flag_minus && parg.precision == -1) {
    while (ind < parg.width) {
      buffer[ind++] = '0';
    }
  }
  while (ind < parg.precision) {
    buffer[ind++] = '0';
  }
  if (!parg.flag_minus) {
    while (ind < parg.width) {
      buffer[ind++] = ' ';
    }
    buffer[ind] = '\0';
    reverse_string(buffer, ind);
  } else {
    reverse_string(buffer, ind);
    while (ind < parg.width) {
      buffer[ind++] = ' ';
    }
    buffer[ind] = '\0';
  }
  return buffer;
}

char *s21_hex(long int num, char *buffer, int capitals, p_arg parg) {
  int ind = 0;
  int sign = 1;
  int base = 16;
  if (num == 0) {
    buffer[ind] = '0';
    ind++;
    buffer[ind] = '\0';
  }
  if (num < 0) {  // base == 10 &&
    sign = -1;
  }
  int not_zero = num != 0 ? 1 : 0;
  while (num != 0) {
    // rest = num % base;
    // if (rest > 9) buffer[ind++] = (rest - 10) + 'a';
    // else buffer[ind++] = rest + '0';
    if (capitals)
      buffer[ind++] = "0123456789ABCDEF"[num % base];
    else
      buffer[ind++] = "0123456789abcdef"[num % base];
    num = num / base;
    // printf("%s\n", buffer);
  }
  // if (parg.flag_hashtag && not_zero) {
  //   if (capitals) {
  //     buffer[ind++] = 'X';
  //     buffer[ind++] = '0';
  //   } else {
  //     buffer[ind++] = 'x';
  //     buffer[ind++] = '0';
  //   }
  // }
  flags(buffer, ind, sign, parg, not_zero);
  return buffer;
}

void flags(char *buffer, int ind, int sign, p_arg parg, int not_zero) {
  if (parg.flag_zero && !parg.flag_minus && parg.precision == -1) {
    if (!parg.flag_blank && !parg.flag_plus && sign == 1) {
      while (ind < parg.width) {
        buffer[ind++] = '0';
      }
    } else {
      while (ind < parg.width - 1) {
        buffer[ind++] = '0';
      }
    }
  }
  while (ind < parg.precision) {
    buffer[ind++] = '0';
    // printf("added 0\n");
  }
  int hex = (parg.specifier == 'X' || parg.specifier == 'x') ? 1 : 0;
  int capitals = 0;
  if (hex) capitals = (parg.specifier == 'X') ? 1 : 0;
  if (parg.flag_hashtag && hex && not_zero) {
    if (capitals) {
      buffer[ind++] = 'X';
      buffer[ind++] = '0';
    } else {
      buffer[ind++] = 'x';
      buffer[ind++] = '0';
    }
  }

  if (sign == -1 && parg.signed_type) {
    buffer[ind++] = '-';
  } else if (parg.flag_plus && parg.signed_type) {
    buffer[ind++] = '+';
  } else if (parg.flag_blank && parg.signed_type) {
    buffer[ind++] = ' ';
    // printf("blank flag\n");
  }
  if (!parg.flag_minus) {
    while (ind < parg.width) {
      buffer[ind++] = ' ';
      // printf("blank width\n");
    }
    buffer[ind] = '\0';
    reverse_string(buffer, ind);
  } else {
    // printf("minus\n");
    reverse_string(buffer, ind);
    while (ind < parg.width) {
      buffer[ind++] = ' ';
      // printf("blank width\n");
    }
    buffer[ind] = '\0';
  }
}

int int_len(long int num) {
  int res = 0;
  if (num < 0) num *= -1;
  while (num > 0) {
    res++;
    num = num / 10;
  }
  return res;
}

int unsigned_int_len(unsigned long int num) {
  int res = 0;
  while (num > 0) {
    res++;
    num = num / 10;
  }
  return res;
}

char *handle_signed_integers(p_arg parg, va_list args) {  // d, i u, c, o, x, X
  long int num1 = va_arg(args, long int);
  char *buffer = NULL;
  // if (parg.precision == -1) parg.precision = 1;
  int go = (parg.specifier == 'd' || parg.specifier == 'i') ? 1 : 0;
  if (go) {
    buffer = calloc(getbuffersizeint(parg, int_len(num1)) + 10, sizeof(char));
    if (parg.length == -1) {
      int num = (int)num1;
      s21_long_itoa(num, buffer, 10, parg);
    } else if (parg.length == 'h') {
      short int num = (short int)num1;
      s21_long_itoa(num, buffer, 10, parg);
    } else {
      long int num = num1;
      s21_long_itoa(num, buffer, 10, parg);
    }
  }
  return buffer;
}

char *handle_octal(p_arg parg, va_list args) {  // d, i u, c, o, x, X
  unsigned long int num1 = va_arg(args, unsigned long int);
  char *buffer = NULL;
  // if (parg.precision == -1) parg.precision = 1;
  int go = (parg.specifier == 'o') ? 1 : 0;
  if (go) {
    buffer = calloc(getbuffersizeint(parg, int_len(num1)) + 10, sizeof(char));
    if (parg.length == -1) {
      unsigned num = (unsigned)num1;
      s21_long_itoa(num, buffer, 8, parg);
    } else if (parg.length == 'h') {
      short unsigned num = (short unsigned)num1;
      s21_long_itoa(num, buffer, 8, parg);
    } else {
      long unsigned num = num1;
      s21_long_itoa(num, buffer, 8, parg);
    }
  }
  return buffer;
}

char *handle_hexadecimal(p_arg parg, va_list args) {  // u, o, x, X
  unsigned long int num1 = va_arg(args, unsigned long int);
  char *buffer = NULL;
  // if (parg.precision == -1) parg.precision = 1;
  int go = (parg.specifier == 'x' || parg.specifier == 'X') ? 1 : 0;
  if (go) {
    int capital = 0;
    if (parg.specifier == 'X') capital = 1;
    buffer = calloc(getbuffersizeint(parg, int_len(num1)) + 10, sizeof(char));
    if (parg.length == -1) {
      unsigned num = (unsigned)num1;
      s21_hex(num, buffer, capital, parg);
    } else if (parg.length == 'h') {
      // unsigned short int num = num1;
      // printf("before conversion to short: %lu\n", num1);
      short num = num1;
      // printf("after conversion to short: %hu\n", num);
      s21_hex(num, buffer, capital, parg);
    } else {
      unsigned long int num = num1;
      s21_hex(num, buffer, capital, parg);
    }
  }
  return buffer;
}

char *handle_unsigned_integers(p_arg parg,
                               va_list args) {  // d, i u, c, o, x, X
  unsigned long int num1 = va_arg(args, unsigned long int);
  char *buffer = NULL;
  // if (parg.precision == -1) parg.precision = 1;
  int go = (parg.specifier == 'u') ? 1 : 0;
  if (go) {
    buffer = calloc(getbuffersizeint(parg, unsigned_int_len(num1)) + 10,
                    sizeof(char));
    if (parg.length == -1) {
      unsigned int num = (unsigned int)num1;
      // s21_unsigned_int_itoa(num, buffer, 10, parg);
      s21_unsigned_long_itoa(num, buffer, 10, parg);
    } else if (parg.length == 'h') {
      unsigned short int num = (unsigned short int)num1;
      // s21_unsigned_short_itoa(num, buffer, 10, parg);
      s21_unsigned_long_itoa(num, buffer, 10, parg);
    } else {
      unsigned long int num = num1;
      s21_unsigned_long_itoa(num, buffer, 10, parg);
    }
  }
  return buffer;
}
