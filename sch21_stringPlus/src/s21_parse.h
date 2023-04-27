#include "s21_string.h"
#ifndef SRC_S21_PARSE_H_
#define SRC_S21_PARSE_H_

typedef struct parse_arg {
  int flag_plus;
  int flag_minus;
  int flag_blank;
  int flag_hashtag;
  int flag_zero;
  int width;
  int precision;
  char length;
  char specifier;
  int error;
  int percentage;
  int signed_type;
} p_arg;

p_arg parginit();
int exists_char(char ch, char *string, int n);
int dot_next(char *string);
char *parse_flags(p_arg *parg, char *parse_start);
char *parse_width(p_arg *parg, char *parse_start);
char *parse_precision(p_arg *parg, char *parse_start);
char *parse_length(p_arg *parg, char *parse_start);
char *parse_type(p_arg *parg, char *parse_start);
char *s21_fullparse(char *str, p_arg *structure);

#endif  //  SRC_S21_PARSE_H_