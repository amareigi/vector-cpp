CC = g++
FLAG_C = -c
FLAG_O = -o
ASAN = -g -fsanitize=address
FLAG_COV = --coverage
FLAG_ER = -Wall -Werror -Wextra -std=c++17
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes
FLAG_TESTS = -lgcov -lsubunit -lgtest -lgtest_main

s21_CONTAINERS_CPP = s21_*.cpp
s21_CONTAINERS_O = s21_*.o
OUTDIR = BUILD
TESTDIR = TESTS
LIBDIR = CONTAINERS
SUITE_CASES_CPP = suite_*.cpp
SUITE_CASES_O = suite_*.o

all: clean gcov_report

test:
	rm -rf BUILD
	mkdir BUILD
	for file in $(TESTDIR)/$(SUITE_CASES_CPP); do \
		$(CC) $(FLAG_C) $(FLAG_ER) $(FLAG_COV) $$file -o $(OUTDIR)/$$(basename $$file .cpp).o; \
	done
	$(CC) $(FLAG_ER) -o $(OUTDIR)/tests $(OUTDIR)/$(SUITE_CASES_O) $(FLAG_TESTS)
	./$(OUTDIR)/tests


asan:
	rm -rf BUILD
	mkdir BUILD
	for file in $(TESTDIR)/$(SUITE_CASES_CPP); do \
		$(CC) $(FLAG_C) $(FLAG_ER) $(FLAG_COV) $$file -o $(OUTDIR)/$$(basename $$file .cpp).o; \
	done
	$(CC) $(FLAG_ER) -o $(OUTDIR)/tests $(OUTDIR)/$(SUITE_CASES_O) $(FLAG_TESTS) $(ASAN)
	./$(OUTDIR)/tests

valgrind_test:
	rm -rf BUILD
	mkdir BUILD
	for file in $(TESTDIR)/$(SUITE_CASES_CPP); do \
		$(CC) $(FLAG_C) $(FLAG_ER) $(FLAG_COV) $$file -o $(OUTDIR)/$$(basename $$file .cpp).o; \
	done
	$(CC) $(FLAG_ER) -o $(OUTDIR)/tests $(OUTDIR)/$(SUITE_CASES_O) $(FLAG_TESTS)
	valgrind $(VALGRIND_FLAGS) ./$(OUTDIR)/tests

gcov_report: test
	lcov -c -d $(OUTDIR) -o $(OUTDIR)/test_coverage.info

	lcov -r $(OUTDIR)/test_coverage.info '/usr/*' -o $(OUTDIR)/test_coverage_filtered.info
	lcov -r $(OUTDIR)/test_coverage_filtered.info '*/gtest/*' -o $(OUTDIR)/test_coverage_filtered.info
	lcov -r $(OUTDIR)/test_coverage_filtered.info '*/gtest/internal/*' -o $(OUTDIR)/test_coverage_filtered.info
	lcov -r $(OUTDIR)/test_coverage_filtered.info '*/bits/*' -o $(OUTDIR)/test_coverage_filtered.info
	lcov -r $(OUTDIR)/test_coverage_filtered.info '*/ext/*' -o $(OUTDIR)/test_coverage_filtered.info
	lcov -r $(OUTDIR)/test_coverage_filtered.info '*/suite_*.cpp' -o $(OUTDIR)/test_coverage_filtered.info

	genhtml -o $(OUTDIR)/report $(OUTDIR)/test_coverage_filtered.info
	open $(OUTDIR)/report/index.html

gcov_report_gcov: test
	gcovr --html-details -o $(OUTDIR)/report.html

style_check:
	cp ../materials/linters/.clang-format .
	clang-format -i $(LIBDIR)/*.h $(LIBDIR)/*.tpp $(TESTDIR)/*.cpp
	clang-format -n $(LIBDIR)/*.h $(LIBDIR)/*.tpp $(TESTDIR)/*.cpp
	rm -rf .clang-format

clean:
	-rm -rf BUILD
	-rm -rf *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg *.txt
	-rm -f tests
	-rm -f report
	find . -type d -name 'tests.dSYM' -exec rm -r {} +
