#include "s21_parse.h"

#include "s21_string.h"

#define specifiers                                                            \
  (char[]) {                                                                  \
    'c', 'd', 'i', 'e', 'f', 'E', 'g', 'G', 'o', 's', 'u', 'x', 'X', 'p', 'n' \
  }  // n = 15
#define length_types \
  (char[]) { 'h', 'l', 'L' }
#define n_length_types 3
#define n_specifiers 15

p_arg parginit() {
  p_arg newparg = {0, 0, 0, 0, 0, -1, -1, -1, -1, 0, 0, 0};
  return newparg;
}

int exists_char(char ch, char *string, int n) {
  int res = 0;
  for (int i = 0; i < n && !res; i++) {
    if (ch == string[i]) res = 1;
  }
  return res;
}

int dot_next(char *string) {
  int res = 0;
  if ('.' == *string) res = 1;
  return res;
}

char *parse_flags(p_arg *parg, char *parse_start) {
  int go = 1;
  char *tmp = parse_start;
  if (*tmp == '%') {
    go = 0;
    parg->percentage = 1;
  }
  while (go) {
    if (*tmp == '+') {
      parg->flag_plus = 1;
    } else if (*tmp == '-') {
      parg->flag_minus = 1;
    } else if (*tmp == ' ') {
      parg->flag_blank = 1;
    } else if (*tmp == '#') {
      parg->flag_hashtag = 1;
    } else if (*tmp == '0') {
      parg->flag_zero = 1;
    } else {
      if (*tmp == '\0') parg->error = 1;
      go = 0;
    }
    if (go) {
      tmp++;
    }
  }
  // if (parg->flag_minus && parg->flag_zero) parg->flag_zero = 0; ?????????????
  return tmp;
}

char *parse_width(p_arg *parg, char *parse_start) {
  int go = 1;
  int counter = 0;
  char *tmp = parse_start;
  int raw_num[100] = {0};
  int res_num = 0;
  if (*tmp == '*') {
    parg->width = -2;
    tmp++;
  } else {
    while (go) {
      if (*tmp >= 48 && *tmp <= 57) {
        raw_num[counter] = (*tmp - 48);
        counter++;
        tmp++;
      } else {
        if (*tmp == '\0' ||
            (*tmp != '.' && !exists_char(*tmp, length_types, n_length_types) &&
             !exists_char(*tmp, specifiers, n_specifiers))) {
          parg->error = 1;
        }
        go = 0;
      }
    }
    int raw_end = counter;
    for (int i = 0; i < raw_end; i++, counter--) {
      res_num += (int)(raw_num[i] * pow(10.0, (double)(counter - 1)));
    }
    parg->width = res_num;
  }
  return tmp;
}

char *parse_precision(
    p_arg *parg,
    char *parse_start) {  // we are in this func if there was a dot!!!
  int go = 1;
  int counter = 0;
  char *tmp = parse_start;
  int raw_num[100] = {0};
  int res_num = 0;
  if (*tmp == '*') {
    parg->precision = -2;
    tmp++;
  } else {
    while (go) {
      if (*tmp >= 48 && *tmp <= 57) {
        raw_num[counter] = (*tmp - 48);
        counter++;
        tmp++;
      } else {
        if (*tmp == '\0' || (!exists_char(*tmp, length_types, n_length_types) &&
                             !exists_char(*tmp, specifiers, n_specifiers))) {
          parg->error = 1;
        }
        go = 0;
      }
    }
    int raw_end = counter;
    for (int i = 0; i < raw_end; i++, counter--) {
      res_num += (int)(raw_num[i] * pow(10.0, (double)(counter - 1)));
    }
    if (raw_end)
      parg->precision = res_num;
    else
      parg->precision =
          0;  // there was a dot but no number after -> precision 0
  }
  return tmp;
}

char *parse_length(p_arg *parg, char *parse_start) {
  int go = 1;
  char *tmp = parse_start;
  if (*tmp == 'l') {
    parg->length = 'l';
  } else if (*tmp == 'L') {
    parg->length = 'L';
  } else if (*tmp == 'h') {
    parg->length = 'h';
  } else {
    go = 0;
  }
  if (go) {
    tmp++;
  }
  if (*tmp == '\0' || !exists_char(*tmp, specifiers, n_specifiers)) {
    parg->error = 1;
  }
  return tmp;
}

char *parse_type(p_arg *parg, char *parse_start) {
  int go = 1;
  char *tmp = parse_start;
  if (*tmp == 'c') {
    parg->specifier = 'c';
  } else if (*tmp == 'd') {
    parg->specifier = 'd';
    parg->signed_type = 1;
  } else if (*tmp == 'i') {
    parg->specifier = 'i';
    parg->signed_type = 1;
  } else if (*tmp == 'e') {
    parg->specifier = 'e';
    parg->signed_type = 1;
  } else if (*tmp == 'f') {
    parg->specifier = 'f';
    parg->signed_type = 1;
  } else if (*tmp == 'E') {
    parg->specifier = 'E';
    parg->signed_type = 1;
  } else if (*tmp == 'g') {
    parg->specifier = 'g';
    parg->signed_type = 1;
  } else if (*tmp == 'G') {
    parg->specifier = 'G';
    parg->signed_type = 1;
  } else if (*tmp == 'o') {
    parg->specifier = 'o';
  } else if (*tmp == 's') {
    parg->specifier = 's';
  } else if (*tmp == 'u') {
    parg->specifier = 'u';
  } else if (*tmp == 'x') {
    parg->specifier = 'x';
  } else if (*tmp == 'X') {
    parg->specifier = 'X';
  } else if (*tmp == 'p') {
    parg->specifier = 'p';
  } else if (*tmp == 'n') {
    parg->specifier = 'n';
  } else {
    go = 0;
    parg->error = 1;
  }
  if (go) {
    tmp++;
  }
  return tmp;
}
// returns NULL if any error occured and pointer to the remaining string
// otherwise

char *s21_fullparse(char *str, p_arg *structure) {
  int not_exit = 1;

  //
  char *ptr = parse_flags(structure, str);
  // printf("%s\n", ptr);
  if (structure->error || structure->percentage) not_exit = 0;
  if (not_exit) {
    if (dot_next(ptr)) {
      ptr++;
      ptr = parse_precision(structure, ptr);
    } else {
      ptr = parse_width(structure, ptr);
      if (!structure->error && dot_next(ptr)) {
        ptr++;
        ptr = parse_precision(structure, ptr);
      }
    }
    if (structure->error) not_exit = 0;
  }
  if (not_exit) {
    ptr = parse_length(structure, ptr);
    if (structure->error) not_exit = 0;
  }
  if (not_exit) {
    ptr = parse_type(structure, ptr);
    if (structure->error) not_exit = 0;
  }

  if (!not_exit && !structure->percentage) ptr = NULL;
  return ptr;
}
