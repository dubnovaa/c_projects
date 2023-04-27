#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define flag_e 0
#define flag_i 1
#define flag_v 2
#define flag_c 3
#define flag_l 4
#define flag_n 5
#define flag_h 6
#define flag_s 7
#define flag_f 8
#define flag_o 9
int grep_file(int argc, char *argv[], int flags[10], int optind,
              regex_t regex[1024], int regex_count);
int read_regexes_from_file(char *filename, int *regex_count, int *flags,
                           regex_t regex[1024]);
int main(int argc, char *argv[]) {
  int flag_end = 0;
  int rez;
  regex_t regex[1024];
  int regex_count = 0;
  char *e_regs[1024];
  char *files_regs[1024];
  int file_regs_count = 0;
  int flags[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  while ((rez = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (rez) {
      case 'e': {
        flags[flag_e] = 1;
        e_regs[regex_count++] = optarg;
        break;
      }
      case 'i':
        flags[flag_i] = 1;
        break;
      case 'v':
        flags[flag_v] = 1;
        break;
      case 'c':
        flags[flag_c] = 1;
        break;
      case 'l':
        flags[flag_l] = 1;
        break;
      case 'n':
        flags[flag_n] = 1;
        break;
      case 'h':
        flags[flag_h] = 1;
        break;
      case 's':
        flags[flag_s] = 1;
        break;
      case 'f': {
        flags[flag_f] = 1;
        files_regs[file_regs_count++] = optarg;
        break;
      }
      case 'o':
        flags[flag_o] = 1;
        break;
      case '?':
      default: {
        flag_end = 1;
        printf("found unknown option\n");
        break;
      };
    }
  }
  if ((optind < argc) && !flags[flag_e] & !flags[flag_f]) {
    regex_t preg;
    int rc;
    if (flags[flag_i])
      rc = regcomp(&preg, argv[optind++], REG_ICASE);
    else
      rc = regcomp(&preg, argv[optind++], REG_EXTENDED);
    if (rc != 0) {
      printf("regcomp() failed, returning nonzero (%d)\n", rc);
    } else {
      regex[regex_count++] = preg;
    }
  }
  if (flags[flag_e]) {
    int rc;
    for (int i = 0; i < regex_count; i++) {
      regex_t preg;
      if (flags[flag_i])
        rc = regcomp(&preg, e_regs[i], REG_ICASE);
      else
        rc = regcomp(&preg, e_regs[i], REG_EXTENDED);
      if (rc != 0) {
        printf("regcomp() failed, returning nonzero (%d)\n", rc);
      } else {
        regex[i] = preg;
      }
    }
  }
  if (flags[flag_f]) {
    for (int i = 0; i < file_regs_count; i++) {
      if (read_regexes_from_file(files_regs[i], &regex_count, flags, regex)) {
        flag_end = 1;
      }
    }
  }
  if (!flag_end) grep_file(argc, argv, flags, optind, regex, regex_count);
  for (int i = 0; i < regex_count; i++) {
    regfree(&regex[i]);
  }
}

int read_regexes_from_file(char *filename, int *regex_count, int *flags,
                           regex_t regex[1024]) {
  FILE *file = NULL;
  file = fopen(filename, "r");
  int flag = 0;
  if (file == NULL) {
    printf("file not found\n");
    flag = 1;
  } else {
    char string[1024];
    regex_t preg;
    int rc;
    while (fgets(string, 1024, file)) {
      string[strcspn(string, "\n")] = '\0';
      if (flags[flag_i])
        rc = regcomp(&preg, string, REG_ICASE);
      else
        rc = regcomp(&preg, string, REG_EXTENDED);
      if (rc != 0) {
        printf("regcomp() failed, returning nonzero (%d)\n", rc);
      } else {
        regex[(*regex_count)++] = preg;
      }
    }
  }
  fclose(file);
  return flag;
}

int grep_file(int argc, char *argv[], int flags[10], int optind,
              regex_t regex[1024], int regex_count) {
  int res = 1;
  char string[1024];
  FILE *file = NULL;
  int multiple_files = 0;
  if (optind >= argc) {
    printf("n/a\n");
  } else {
    if (argc - optind > 1) multiple_files = 1;
    while (optind < argc) {  // loop for files
      char *filename = argv[optind++];
      file = fopen(filename, "r");
      if (file == NULL) {
        if (!flags[flag_s]) {
          printf("file not found\n");
          res = 0;
        }
      } else {
        int count_match_lines = 0;
        int count_line = 0;
        while (fgets(string, 1024, file)) {
          count_line++;
          size_t nmatch = 1;
          int wrote_num = 0;
          int wrote_filename = 0;
          int match_count = 0;
          for (int i = 0; i < regex_count; i++) {
            regmatch_t pmatch;
            int rc;
            char *string_copy = string;
            while ((rc = regexec(regex + i, string_copy, nmatch, &pmatch, 0)) ==
                   0) {
              if (flags[flag_o] && !flags[flag_c] && !flags[flag_l]) {
                if (multiple_files && !flags[flag_h] && !wrote_filename) {
                  printf("%s:", filename);
                  wrote_filename = 1;
                }
                if (flags[flag_n] && !wrote_num) {
                  printf("%d:", count_line);
                  wrote_num = 1;
                }
                printf("%.*s\n", (int)(pmatch.rm_eo - pmatch.rm_so),
                       string_copy + pmatch.rm_so);
              }
              string_copy += pmatch.rm_eo;
              match_count++;
            }
          }
          if (match_count > 0) count_match_lines++;
          if (flags[flag_v] && !flags[flag_l] && !flags[flag_c] &&
              !flags[flag_o] && match_count == 0) {
            if (multiple_files && !flags[flag_h]) {
              printf("%s:", filename);
            }
            if (flags[flag_n]) {
              printf("%d:", count_line);
            }
            printf("%s", string);
          }
          if (!(flags[flag_v] || flags[flag_c] || flags[flag_l] ||
                flags[flag_o]) &&
              match_count > 0) {
            if (multiple_files && !flags[flag_h]) {
              printf("%s:", filename);
            }
            if (flags[flag_n]) {
              printf("%d:", count_line);
            }
            printf("%s", string);
          }
        }
        if (flags[flag_c]) {
          if (multiple_files && !flags[flag_h]) {
            printf("%s:", filename);
          }
          if (!flags[flag_v])
            printf("%d\n", count_match_lines);
          else
            printf("%d\n", count_line - count_match_lines);
        }
        if (flags[flag_l]) {
          if (!flags[flag_v] && count_match_lines > 0)
            printf("%s\n", filename);
          else if (flags[flag_v] && (count_line - count_match_lines) > 0)
            printf("%s\n", filename);
        }
      }
      fclose(file);
    }
  }
  return res;
}