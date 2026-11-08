all: rbt-tests

rbt-tests: RedBlackTree.cpp RedBlackTree.h RedBlackTreeTests.cpp
	g++ -std=c++17 -Wall -Wextra -g RedBlackTree.cpp RedBlackTreeTests.cpp -o rbt-tests

test: rbt-tests
	./rbt-tests

clean:
	rm -f rbt-tests
	rm -rf rbt-tests.dSYM
