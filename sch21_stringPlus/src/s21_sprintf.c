#include "s21_floats.h"
#include "s21_itoa.h"
#include "s21_parse.h"
#include "s21_string.h"

int getbuffersizestr(p_arg parg, int strlen);

int getbuffersizestr(p_arg parg, int strlen) {
  int buffersize = 0;
  if (parg.precision > -1 && parg.precision <= strlen) {
    buffersize = parg.precision;
  } else {
    buffersize = strlen;
  }
  if (parg.width > buffersize) {
    buffersize = parg.width;
  }

  return buffersize;
}

int wstrlen(const wchar_t *wstr) {
  int count = 0;
  for (; *wstr; wstr++, count++) {
  }
  return count;
}

char *wStrtoStr(const wchar_t *wstr) {
  char *newstr = NULL;
  int len = wstrlen(wstr);
  newstr = calloc((len + 1) + 1, sizeof(char));
  for (int i = 0; i < len + 1; i++) {
    newstr[i] = (char)wstr[i];
  }
  return newstr;
}

char *getBuf_string(va_list args, p_arg parg) {
  char *mstr = NULL;
  char *save_free = NULL;
  if (parg.length == 'l') {
    wchar_t *wmstr = va_arg(args, wchar_t *);
    if (wmstr == NULL) {
      mstr = NULL_STR;
    } else {
      mstr = wStrtoStr(wmstr);
      save_free = mstr;
    }
  } else {
    mstr = va_arg(args, char *);
    if (mstr == NULL) {
      mstr = NULL_STR;
    }
  }
  int mlen = s21_strlen(mstr);
  int buffersize = getbuffersizestr(parg, mlen);
  int paddingnum = (parg.precision > -1 && parg.precision <= mlen)
                       ? (buffersize - parg.precision)
                       : (buffersize - mlen);
  char *buffer = calloc(buffersize + 1, sizeof(char));
  char pad = (parg.flag_zero == 1) ? '0' : ' ';
  for (int i = 0; i < buffersize; i++) {
    if (parg.flag_minus) {
      if (i >= (buffersize - paddingnum)) {
        buffer[i] = ' ';
      } else {
        buffer[i] = *mstr;
        mstr++;
      }
    } else {
      if (i < paddingnum) {
        buffer[i] = pad;
      } else {
        buffer[i] = *mstr;
        mstr++;
      }
    }
  }
  free(save_free);
  return buffer;
}

char *getBuf_char(va_list args, p_arg parg) {
  char mch;
  if (parg.length == 'l') {
    wchar_t wmch = va_arg(args, unsigned int);
    mch = (char)wmch;
  } else {
    mch = va_arg(args, int);
  }
  int buffersize = (parg.width == 0) ? 1 : parg.width;
  char *buffer = calloc(buffersize + 1, sizeof(char));
  char pad = (parg.flag_zero == 1) ? '0' : ' ';
  for (int i = 0; i < buffersize; i++) {
    if (parg.flag_minus) {
      if (i >= 1) {
        buffer[i] = ' ';
      } else {
        buffer[i] = mch;
      }
    } else {
      if (i < (buffersize - 1)) {
        buffer[i] = pad;
      } else {
        buffer[i] = mch;
      }
    }
  }
  return buffer;
}

char *getBuf_any(va_list args, p_arg parg) {
  char *buffer = NULL;
  if (parg.specifier == 's') {
    buffer = getBuf_string(args, parg);
  } else if (parg.specifier == 'c') {
    parg.precision = -1;
    buffer = getBuf_char(args, parg);
  } else if (parg.specifier == 'd' || parg.specifier == 'i') {
    buffer = handle_signed_integers(parg, args);
  } else if (parg.specifier == 'x' || parg.specifier == 'X') {
    buffer = handle_hexadecimal(parg, args);
  } else if (parg.specifier == 'o') {
    buffer = handle_octal(parg, args);
  } else if (parg.specifier == 'u') {
    buffer = handle_unsigned_integers(parg, args);
  } else if (parg.specifier == 'f' || parg.specifier == 'E' ||
             parg.specifier == 'e') {
    buffer = handle_doubles(parg, args);
  }

  return buffer;
}

int s21_sprintf(char *str, const char *format, ...) {
  char *cur = str;
  va_list args;
  va_start(args, format);
  char *string = (char *)format;
  while (*string) {
    if (*string == '%') {
      p_arg structure = parginit();
      string = s21_fullparse((string + 1), &structure);
      if (structure.percentage) {
        *cur = '%';
        cur++;
        string++;
      } else {
        char *buffer = getBuf_any(args, structure);
        int bflen = s21_strlen(buffer);
        for (int i = 0; i < bflen; i++) {
          *cur = buffer[i];
          cur++;
        }
        free(buffer);
      }
    } else {
      *cur = *string;
      cur++;
      string++;
    }
    if (*string == '\0') {
      *cur = *string;
    }
  }
  return 0;
}
