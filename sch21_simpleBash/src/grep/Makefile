CC=gcc
CFLAGS=-Wall -Werror -Wextra

all: clean 
	$(CC) $(CFLAGS) grep.c -o s21_grep

s21_grep: all

try:
	$(CC) $(CFLAGS) try.c -o try_grep

clean:
	rm -rf s21_grep
