.PHONY: qmake, build, tests, leaks, style, install, clean, uninstall, dist, dvi

all: install

qmake:
	mkdir -p build && cd build && qmake ..

build: qmake
	cd build && make

tests:
	gcc ./tests.cc ./Model/model.cc -lstdc++ -lgtest -std=c++17 -Wall -Werror -Wextra -o tests
	./tests

leaks: tests
	leaks -atExit -- ./tests

style:
	cp ../materials/linters/.clang-format ./
	clang-format -n Model/*.cc Model/*.h ./*.cc View/*.cc View/*.h Controller/*.cc Controller/*.h
	rm .clang-format

install: build
	mkdir $(HOME)/Desktop/SmartCalc_v2.0/
	cp -rf build/SmartCalc2.app $(HOME)/Desktop/SmartCalc_v2.0/
	make clean

clean:
	rm -rf build ./*.o ./*.a ./a.out ./*.tar ./*.gcno ./*.gcda ./gcov_report *.info ./*.info tests

uninstall: clean
	rm -rf build*
	rm -rf $(HOME)/Desktop/SmartCalc_v2.0

dist:
	mkdir SmartCalc_v2.0/
	mkdir SmartCalc_v2.0/src
	cp Makefile Controller/* Model/* View/* *.pro *.user *.cc SmartCalc_v2.0/src/
	tar cvzf SmartCalc_v2.0.tgz SmartCalc_v2.0/
	mv SmartCalc_v2.0.tgz $(HOME)/Desktop/
	rm -rf SmartCalc_v2.0/

dvi:
	open README.md
