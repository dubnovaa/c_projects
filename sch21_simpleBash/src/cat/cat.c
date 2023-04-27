#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define flag_b 0
#define flag_ev 1
#define flag_e 2
#define flag_n 3
#define flag_s 4
#define flag_tv 5
#define flag_t 6
int read_file_simple(char *filename, FILE *file);
int cat(FILE *file, char *argv[], int argc, int flags[7]);
int find_first_file_index(char *argv[], int argc);
void cat_v(char ch);
int main(int argc, char *argv[]) {
  FILE *file = NULL;
  int flags[7] = {0, 0, 0, 0, 0, 0, 0};
  const char *short_options = "benstET";

  const struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};

  int rez;
  int option_index = -1;
  int flag_end = 0;
  while ((rez = getopt_long(argc, argv, short_options, long_options,
                            &option_index)) != -1) {
    switch (rez) {
      case 'b': {
        flags[flag_b] = 1;
        break;
      };
      case 'e': {
        flags[flag_ev] = 1;
        break;
      };
      case 'n': {
        flags[flag_n] = 1;
        break;
      };
      case 's': {
        flags[flag_s] = 1;
        break;
      };
      case 't': {
        flags[flag_tv] = 1;
        break;
      };
      case 'E': {
        flags[flag_e] = 1;
        break;
      };
      case 'T': {
        flags[flag_t] = 1;
        break;
      };
      case '?':
      default: {
        flag_end = 1;
        printf("found unknown option\n");
        break;
      };
    };
    option_index = -1;
  };
  // printf("%s", filename);
  if (!flag_end) cat(file, argv, argc, flags);
}

int read_file_simple(char *filename, FILE *file) {
  int res = 1;
  char ch;
  file = fopen(filename, "r");
  if (file == NULL) {
    printf("n/a\n");
    res = 0;
  } else {
    while (ch != EOF) {
      ch = fgetc(file);
      printf("%c", ch);
    }
  }
  fclose(file);
  return res;
}

int find_first_file_index(char *argv[], int argc) {
  int count = 1;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      count = i;
      break;
    }
  }
  return count;
}

int cat(FILE *file, char *argv[], int argc, int flags[7]) {
  int res = 1;
  char ch;
  int first_file = find_first_file_index(argv, argc);
  for (int i = first_file; i < argc; i++) {
    int first_iteration = 1;
    int count = 0;
    int count_all_lines = 0;
    int last_enter = 0;
    char *filename = argv[i];
    file = fopen(filename, "r");
    if (file == NULL) {
      printf("n/a\n");
      res = 0;
    } else {
      while ((ch = fgetc(file)) != EOF) {
        if (ch == '\0') printf("NULL\n");
        if (ch == '\n') {
          // last_enter = 1;
          // count_all_lines++;
          if (flags[flag_s] && last_enter > 1) continue;  // FLAG S
          if (last_enter == 0) {
            // last_enter++;
            count++;
            // count_all_lines++;
          }
          if (flags[flag_n] && !flags[flag_b] &&
              (last_enter > 0 || first_iteration == 1)) {
            count_all_lines++;
            printf("%6d\t", count_all_lines);
          }
          // FLAG E
          if (flags[flag_e] || flags[flag_ev]) {
            printf("$");
          }

          last_enter++;
          printf("%c", ch);
        } else {
          if (first_iteration) {
            count++;
            // count_all_lines++;
          }
          // FLAG b
          if (flags[flag_b] && (last_enter > 0 || first_iteration == 1)) {
            // printf("FLAG B");
            printf("%6d\t", count);
            // last_enter = 0;
          } else if (flags[flag_n] &&
                     (last_enter > 0 || first_iteration == 1)) {  // FLAG n
            count_all_lines++;
            printf("%6d\t", count_all_lines);
            // last_enter = 0;
          }
          if ((flags[flag_t] || flags[flag_tv]) && ch == '\t') {
            // printf("tab");
            printf("^I");
          } else if (flags[flag_ev] || flags[flag_tv]) {
            cat_v(ch);
          } else {
            printf("%c", ch);
          }
          last_enter = 0;
        }
        if (first_iteration > 0) first_iteration--;
      }
    }
    fclose(file);
  }
  return res;
}

void cat_v(char ch) {
  if (ch < -96) {
    printf("M-^%c", ch + 192);
  } else if (ch < 0) {
    printf("M-%c", ch + 128);
  } else if (ch == 9 || ch == 10) {
    putchar(ch);
  } else if (ch < 32) {
    printf("^%c", ch + 64);
  } else if (ch < 127) {
    putchar(ch);
  } else {
    printf("^?");
  }
}