CC = g++
FLAG_COV = -O2 -g --coverage -fno-inline --coverage 
FLAG_ER = -Wall -Werror -Wextra -std=c++17
#FLAG_TESTS = -L/usr/local/lib -lgtest -pthread -lgtest_main -lm -lgcov -fprofile-arcs -ftest-coverage -Wno-deprecated-copy -Wno-unused-parameter
FLAG_TESTS = -L/usr/local/lib -lgtest -pthread -lgtest_main -lm -lgcov
OUTDIR = BUILD
SUITE_CASES_O = BUILD/*.o
s21_CONTAINERS_SPP_TESTS = tests/gtest_start_point.cc
TESTS_CPP = tests/*.cc
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes -s

all: test

test: clean build
	$(CC) $(FLAG_ER) $(FLAG_COV) $(TESTS_CPP) -o $(OUTDIR)/test $(FLAG_TESTS)
	./$(OUTDIR)/test

gcov_report: make_report report

make_report:
	@gcovr --html-details  --exclude-unreachable-branches --filter='.*\.inc' -o $(OUTDIR)/report.html


report:
	@echo "..открытие отчета."      
	@open $(OUTDIR)/report.html

valgrind_test: 
	valgrind $(VALGRIND_FLAGS) ./$(OUTDIR)/test

style_check:
	@echo "Проверка стиля кода..."
	@cp ../materials/linters/.clang-format ./
	@find . -name "*.inc" -o -name "*.h" | xargs clang-format -n > tmp.log 2>&1
	@if ! grep -q "warning" tmp.log; then \
		echo "\033[32mСтиль кода соответствует.\033[0m"; \
		else \
		echo "\033[31mСтиль кода не соответствует.\033[0m"; \
		fi
	@rm -rf .clang-format tmp.log

style_fix:
	@cp ../materials/linters/.clang-format ./
	@find . -name "*.inc" -o -name "*.h" | xargs clang-format -i
	@echo "\033[33mСтиль кода исправлен.\033[0m";
	@rm -rf .clang-format


clean:
	@-rm -rf BUILD
	@echo "Папка очищена."

build:
	@-rm -rf BUILD/*
	@mkdir -p BUILD
