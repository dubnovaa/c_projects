CC=gcc -g
CFLAGS=-Wall -Werror -Wextra -std=c11

all: clean s21_matrix.a

C_FILES=$(wildcard s21_*.c)
O_FILES=*.o

ifeq ($(UNAME), Linux)
 GFLAGS =  -lm -lsubunit -lpthread -lrt
endif

s21_matrix.a: all_functions
	ar rc s21_matrix.a $(O_FILES)
	ranlib s21_matrix.a
	rm -rf *.o

test: clean s21_matrix.a
	$(CC) $(FLAGS) s21_matrix.a test.c -lcheck -o test
	./test

gcov_report:
	mkdir -p html
	$(CC) $(FLAGS) $(C_FILES) test.c -lcheck -o test --coverage
	./test
	rm test*.gcda test*.gcno
	gcov -l -p -c s21_*.gcno
	gcovr -o html/gcov_report.html --html --html-details
	open html/gcov_report.html
	rm *.gcno *.gcda *.gcov

all_functions: $(C_FILES)
	gcc -c $(CFLAGS) $(C_FILES)

style: clean
	mv ../materials/linters/.clang-format .
	clang-format -i *.c 
	clang-format -i *.h
	clang-format -n *.c
	clang-format -n *.h
	mv .clang-format ../materials/linters/

clean:
	rm -rf *.o *.a try test .gcno *.gcda *.gcov *.html *.css html/*
	rm -rf html

rebuild:
	clean all
