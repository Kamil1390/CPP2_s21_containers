.PHONY: all test gcov_report check rebuild clean memcheck
CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LC = lcov -c -d .
OS = $(shell uname -s)

all: test

clean:
	rm -rf *.o *.gcno *.gcda *.info test.out
	rm -rf ./report
	rm -rf *.dSYM
	rm -rf *.gch
	rm -rf test
	rm -rf gcov_test
	rm -rf gcov_report/

rebuild: clean all

test: clean
	$(CC) $(CFLAGS) unit_tests.cc -lgtest -pthread -o test
	./test

memcheck: test
ifeq ($(OS), Darwin)
	leaks -atExit -- ./test
else
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test
endif

gcov_report: clean
	$(CC) $(CFLAGS) $(GCOVFLAGS) -o gcov_test -lgtest -pthread  unit_tests.cc
	./gcov_test
	$(LC) -t "gcov_report" --no-external -o report.info || true
	geninfo . --ignore-errors mismatch --output-filename report.info
	genhtml -o gcov_report report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./gcov_report/index-sort-f.html

check:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.cc
	clang-format -n *.h
	rm -rf .clang-format
