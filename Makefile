all: rbt-tests-first-step

rbt-tests-first-step: RedBlackTree.cpp RedBlackTree.h RedBlackTreeTestsFirstStep.cpp
	c++ -std=c++17 -Wall -Wextra -g RedBlackTree.cpp RedBlackTreeTestsFirstStep.cpp -o rbt-tests-first-step

test: rbt-tests-first-step
	./rbt-tests-first-step

clean:
	rm -f rbt-tests-first-step
	rm -rf rbt-tests-first-step.dSYM
