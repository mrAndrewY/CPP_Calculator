CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
TESTFLAGS = -lgtest -lgtest_main -lpthread
SOURCES = *.cc
SRC_TEST ="tests/test.cc"  
OBJECTS = *.o
OS := $(shell uname)

all: s21_calc_oop.a

dist:	

	tar -cvzf calc_dist.tar.gz *.cc calculator/*.cc


dvi: 
	latex calc_manual.tex

install:
	if ! [ -d "calculator/build" ]; then \
	mkdir calculator/build; \
	fi 
	cd calculator/build; cmake -B .;  \
	cmake ../
	cd calculator/build&&make 
	if [ $(OS) = "Darwin" ]; then \
	ln -s "$(PWD)/calculator/build/s21_calc_c_plus_plus.app" ~/Desktop/calc; \
	else \
	./calculator/build/s21_calc_c_plus_plus; \
	fi
clean:
	rm -f *.o *.a *.gcda *.gcno *.gcov *.out *.html *.info *.gch
	rm -f test
	rm -rf s21_calc_report test.dSYM

uninstall: clean
	rm -rf calculator/build/* ~/Desktop/calc


s21_calc_oop.a:
	$(CC) $(CFLAGS) $(LDFLAGS) -c -g  $(SOURCES)
	ar rc s21_calc_oop.a $(OBJECTS)
	ranlib s21_calc_oop.a
	rm -f *.o

test: s21_calc_oop.a 
	$(CC) $(CFLAGS) $(SRC_TEST) -c 
	$(CC) $(CFLAGS) --coverage  test*o $(SOURCES) s21_calc_oop.a $(TESTFLAGS) -o test
	./test

retest: clean test

fsanit: s21_calc_oop.a
	$(CC)  $(CFLAGS) -g --coverage -fsanitize=address -fsanitize=leak $(SRC_TEST) s21_calc_oop.a $(TESTFLAGS)
	./a.out
	rm -f a.out *.gcno *.gcda *.a

format: 
	clang-format --style=Google -i *.cc *.h calculator/main.cc calculator/deposit_form.h calculator/credit_form.h calculator/view.h  calculator/deposit_form.cc calculator/credit_form.cc calculator/view.cc
	clang-format --style=Google -n *.cc *.h calculator/main.cc calculator/deposit_form.h calculator/credit_form.h calculator/view.h  calculator/deposit_form.cc calculator/credit_form.cc calculator/view.cc

gcov_report: test
	lcov -t "s21_calc" -o s21_calc.info -c -d .
	genhtml -o s21_calc_report s21_calc.info
	rm -f *.gcda *.gcno *.gcov *.info test
	open s21_calc_report/index.html

gcov_report1: test
	gcov *.gcda
	gcovr
	mkdir s21_calc_report
	gcovr --html-details s21_calc_report/index.html
	rm -f *.gcov *.gcda *.gcno test
	open s21_calc_report/index.html

