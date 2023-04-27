#include "s21_itoa.h"
#include "s21_parse.h"
#include "s21_string.h"

int count_e(double num) {
  int e_count = 0;
  if (num < 0.0) {
    num = num * (-1);
  }
  if (num > 1.0) {
    while (num > 10.0) {
      num = num / 10;
      e_count++;
    }
  } else {
    while (num < 1.0) {
      num = num * 10;
      e_count++;
    }
  }
  return e_count;
}

void itoa(int n, char arr[]) {
  int i, sign;
  if ((sign = n) < 0) n = -n;
  i = 0;
  do {
    arr[i++] = n % 10 + 48;
  } while ((n /= 10) > 0);
  if (sign < 0) arr[i++] = '-';
  arr[i] = '\0';
  reverse_string(arr, i);
}

double covnertDoubleToE(double num, int e_value) {
  double new_double = 0.0;
  if (num > 1.0) {
    new_double = num / pow(10.0, e_value);
  } else {
    new_double = num * pow(10.0, e_value);
  }
  return new_double;
}

int getbuffersizedouble(p_arg parg, int strlen) {
  int buffersize = 0;
  if (parg.width >= strlen) {
    buffersize = parg.width + 1;
  } else
    buffersize = strlen;
  return buffersize;
}
int setEnotation(char *buffer, int num, int sign, int eType) {
  int counter = 0;
  char str_e_num[10] = {0};
  itoa(num, str_e_num);
  int numlen = s21_strlen(str_e_num);
  reverse_string(str_e_num, numlen);
  for (int i = 0; i < numlen; i++) {
    buffer[i] = str_e_num[i];
    counter++;
  }
  if (num < 10) {
    buffer[counter++] = '0';
  }
  buffer[counter++] = sign == 1 ? '+' : '-';
  buffer[counter++] = eType;
  return counter;
}

char *s21_double_tostr(long double num, char *buffer, p_arg parg) {
  int ind = 0;
  int sign = 1;
  int not_nan = 1;
  // if (parg.length == 'L') long double num = va_arg(args, long double);
  // else {
  //     double num = va_arg(args, double);
  // }
  if (isnan(num)) {
    buffer[0] = parg.specifier == 'E' ? 'N' : 'n';
    buffer[1] = parg.specifier == 'E' ? 'A' : 'a';
    buffer[2] = parg.specifier == 'E' ? 'N' : 'n';
    ind = 3;
    not_nan = 0;
  }
  if (num < 0) {
    sign = -1;
    num = num * (-1);
  }
  int e_notation_shift = 0;
  if (not_nan & (parg.specifier == 'e' || parg.specifier == 'E')) {
    int e_sign = num > 1.0 ? 1 : 0;
    // function to set e notation value to the end(reversed start) of the buffer
    int e_value = count_e(num);
    // printf("e value:::%d\n", e_value);
    num = covnertDoubleToE(num, e_value);
    e_notation_shift = setEnotation(buffer, e_value, e_sign, parg.specifier);
    ind += e_notation_shift;
  }

  if (parg.precision == -1) parg.precision = 6;
  if (num == 0) {
    // printf("im here\n");
    int count = 0;
    while (count < parg.precision) {
      buffer[ind++] = '0';
      // printf("count: %d\n", count);
      count++;
    }
    if (parg.precision > 0 || parg.flag_hashtag) buffer[ind++] = '.';
    buffer[ind++] = '0';
    // buffer[ind] = '\0';
    // printf("im here 2\n");
  }

  int minus = 0;
  if (parg.precision != -1) {
    if (num < 1 && num > 0) {
      minus = 1;
      num += 1;
    }
    if (parg.specifier == 'f') {
      num = ceil(num * pow(10, parg.precision) - 0.5);  // / pow(10, precision);
    } else {
      num = round(num * pow(10, parg.precision));
    }
  }
  long long int num1 = (long long int)num;

  // printf("%lld\n", num1);
  int rest;
  while (num1 > 0) {
    rest = num1 % 10;
    // HERE
    if ((ind == parg.precision + e_notation_shift) &
        ((parg.precision != 0) || parg.flag_hashtag))
      buffer[ind++] = '.';
    if ((ind == parg.precision + 1) && minus)
      buffer[ind++] = '0';
    else {
      if (rest > 9)
        buffer[ind++] = (rest - 10) + 'a';
      else
        buffer[ind++] = rest + '0';
    }
    num1 = num1 / 10;
  }

  if (parg.flag_zero && !parg.flag_minus && not_nan) {
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
  if (sign == -1) {
    buffer[ind++] = '-';
  } else if (parg.flag_plus) {
    buffer[ind++] = '+';
  } else if (parg.flag_blank) {
    buffer[ind++] = ' ';
  }
  if (!parg.flag_minus) {
    while (ind < parg.width) {
      buffer[ind++] = ' ';
    }
    buffer[ind] = '\0';
    reverse_string(buffer, ind);
    // printf("reversed not minus\n");
  } else {
    // printf("|%s|\n", buffer);
    reverse_string(buffer, ind);
    while (ind < parg.width) {
      buffer[ind++] = ' ';
    }
    buffer[ind] = '\0';
    // printf("reversed minus\n");
  }

  return buffer;
}

int double_len(double num, int precision) {
  int len = 0;
  len += int_len(floor(num)) + 1;
  if (precision > 0)
    len += 2 * precision;
  else if (precision == -1)
    len += 2 * 6;
  return len;
}

char *handle_doubles(p_arg parg, va_list args) {  // d, i u, c, o, x, X
  char *buffer = NULL;
  // if (parg.precision == -1) parg.precision = 1;
  int go =
      (parg.specifier == 'f' || parg.specifier == 'E' || parg.specifier == 'e')
          ? 1
          : 0;
  if (go) {
    // printf("%d\n", getbuffersizedouble(parg, double_len(num1,
    // parg.precision)));
    if (parg.length != 'L') {
      double num = va_arg(args, double);
      buffer =
          calloc(getbuffersizedouble(parg, double_len(num, parg.precision)) + 1,
                 sizeof(char));
      // NULL CHECK
      s21_double_tostr(num, buffer, parg);
    } else {
      long double num = va_arg(args, long double);
      buffer =
          calloc(getbuffersizedouble(parg, double_len(num, parg.precision)) + 1,
                 sizeof(char));
      // NULL CHECK
      s21_double_tostr(num, buffer, parg);
    }
  }
  return buffer;
}
