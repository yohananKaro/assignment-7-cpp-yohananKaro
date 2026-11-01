CXX=clang++
CXXFLAGS=-std=c++23 -Werror -Wsign-conversion
TIDY_FLAGS=-checks=bugprone-*,-bugprone-easily-swappable-parameters,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-* --warnings-as-errors=*
TIDY_CONFIG=-config='{CheckOptions: [{key: cppcoreguidelines-special-member-functions.AllowMissingMoveFunctions, value: true}]}'
TIDY_EXCLUDE=test.cpp StudentTest.cpp

# Header-only templates — no .cpp files for classes
# Only main.cpp and test.cpp are compiled.

all: demo
	./demo

demo: main.o
	$(CXX) $(CXXFLAGS) $^ -o demo

grade: test tidy

test: TestRunner.o student_test
	$(CXX) $(CXXFLAGS) TestRunner.o -o test
	./test

student_test:
	@count=$$(find StudentTest.cpp 2>/dev/null | wc -l); \
	if [ $$count -eq 0 ]; then \
		echo "ERROR: StudentTest.cpp not found. You must create StudentTest.cpp with at least 20 test cases."; \
		exit 1; \
	fi; \
	true

TestRunner.o: test.cpp doctest.h
	$(CXX) $(CXXFLAGS) --compile test.cpp -o TestRunner.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) --compile main.cpp -o main.o

tidy:
	clang-tidy $(filter-out $(TIDY_EXCLUDE), $(wildcard *.cpp) $(wildcard *.hpp)) $(TIDY_FLAGS) $(TIDY_CONFIG) -- $(CXXFLAGS)

clean:
	rm -f *.o demo test

.PHONY: all test clean tidy student_test grade
