
#include <iostream>
#include <cassert>
#include <random>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include "RedBlackTree.h"

using namespace std;

void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	assert(rbt.ToInfixString() == "");
	
	cout << "PASSED!"<< endl << endl;
}

void TestConstructor(){
	cout << "Testing Constructor W/Int Input..." << endl;
	RedBlackTree rbt = RedBlackTree(15);
	assert(rbt.ToPrefixString() == " B15 ");

	cout << "PASSED!"<< endl << endl;
}

void TestInsertFirstNode(){
	cout << "Testing Insert One Node..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	assert(rbt.ToPrefixString() == " B30 ");

	cout << "PASSED!" << endl << endl;
}


void TestInsertSecondNode(){
	cout << "Testing Insert Second Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	assert(rbt->ToPrefixString() == " B30  R15 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	assert(rbt->ToPrefixString() == " B30  R45 ");	
	delete rbt;

	cout << "PASSED!" << endl << endl;
}


void TestInsertThirdNode(){
	cout << "Testing Insert Third Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10); // left-left
	assert(rbt->ToPrefixString() == " B15  R10  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(25); // left-right
	assert(rbt->ToPrefixString() == " B25  R15  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45); // no rotation
	assert(rbt->ToPrefixString() == " B30  R15  R45 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(10);
	rbt->Insert(30);
	rbt->Insert(20); // right-left
	assert(rbt->ToPrefixString() == " B20  R10  R30 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(10);
	rbt->Insert(20);
	rbt->Insert(30); // right-right
	assert(rbt->ToPrefixString() == " B20  R10  R30 ");
	delete rbt;

	cout << "PASSED!" << endl << endl;
}

void TestInsertFourthNode(){
	cout << "Testing Insert Fourth Node..." << endl;

	RedBlackTree rbt;
	rbt.Insert(30);
	rbt.Insert(15);
	rbt.Insert(45);
	rbt.Insert(10);
	assert(rbt.ToPrefixString() == " B30  B15  R10  B45 ");
	
	cout << "PASSED!" << endl << endl;
}

void TestInsertFifthNode(){
	cout << "Testing Insert Fifth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(25);
	assert(rbt->ToPrefixString() == " B30  B15  R10  R25  B45 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(50);
	rbt->Insert(60);
	assert(rbt->ToPrefixString() == " B30  B15  B50  R45  R60 ");
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestDuplicateInsert(){
	cout << "Testing Duplicate Insert..." << endl;

	RedBlackTree rbt;
	rbt.Insert(30);
	rbt.Insert(15);
	bool threw = false;
	try { rbt.Insert(15); } catch (const invalid_argument&) { threw = true; }
	assert(threw);
	assert(rbt.Size() == 2);
	assert(rbt.ToPrefixString() == " B30  R15 ");

	cout << "PASSED!" << endl << endl;
}


void TestToStrings(){
	cout << "Testing ToString Methods..." << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(12);
	rbt.Insert(11);
	rbt.Insert(15);
	rbt.Insert(5);
	rbt.Insert(13);
	rbt.Insert(7);

	assert(rbt.ToPrefixString() == " B12  B7  R5  R11  B15  R13 ");
	assert(rbt.ToInfixString() == " R5  B7  R11  B12  R13  B15 ");
	assert(rbt.ToPostfixString() == " R5  R11  B7  R13  B15  B12 ");

	cout << "PASSED!" << endl << endl;
}

void TestInsertRandomTests(){
	cout << "Testing Random Insert Stuff..." << endl;
	cout << "\t This test passes if it doesn't crash and valgrind reports no issues" << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(13);
	rbt->Insert(20);
	rbt->Insert(12);
	cout << endl;
	delete rbt;
	
	
	rbt = new RedBlackTree();
	rbt->Insert(12);
	rbt->Insert(11);
	rbt->Insert(15);
	rbt->Insert(5);
	rbt->Insert(13);
	rbt->Insert(7);
	delete rbt;
	
	
	rbt = new RedBlackTree();
	rbt->Insert(12);
	rbt->Insert(10);
	rbt->Insert(8);
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestCopyConstructor(){
	cout << "Testing Copy Constructor..." << endl;

	RedBlackTree rbt1 = RedBlackTree();
	rbt1.Insert(11);
	rbt1.Insert(23);
	rbt1.Insert(9);
	rbt1.Insert(52);
	rbt1.Insert(31);
	rbt1.Insert(4);

	assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

	RedBlackTree rbt2 = RedBlackTree(rbt1);

	assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

	rbt1.Insert(200);
	assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());

	cout << "PASSED!" << endl << endl;
}






void TestContains(){
	cout << "Testing Contains..." << endl;

	RedBlackTree *rbt = new RedBlackTree();
	assert(rbt->Contains(6) == false);
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(17);
	rbt->Insert(29);
	rbt->Insert(34);
	
	assert(rbt->Contains(34));
	assert(rbt->Contains(40));
	assert(rbt->Contains(12));
	assert(rbt->Contains(33) == false);
	delete rbt;

	cout << "PASSED!" << endl << endl;
}




void TestGetMinimumMaximum(){
	cout << "Testing Get Minimum and Get Maximum..." << endl;

	RedBlackTree rbt;
	bool minThrew = false;
	bool maxThrew = false;
	try { rbt.GetMin(); } catch (const out_of_range&) { minThrew = true; }
	try { rbt.GetMax(); } catch (const out_of_range&) { maxThrew = true; }
	assert(minThrew && maxThrew);

	rbt.Insert(40);
	assert(rbt.GetMin() == 40);
	assert(rbt.GetMax() == 40);
	rbt.Insert(20);
	rbt.Insert(60);
	rbt.Insert(10);
	rbt.Insert(70);
	assert(rbt.GetMin() == 10);
	assert(rbt.GetMax() == 70);

	cout << "PASSED!" << endl << endl;
}

void TestSize(){
	cout << "Testing Size..." << endl;

	RedBlackTree rbt;
	assert(rbt.Size() == 0);
	rbt.Insert(40);
	assert(rbt.Size() == 1);
	rbt.Insert(20);
	rbt.Insert(60);
	assert(rbt.Size() == 3);
	RedBlackTree copy(rbt);
	assert(copy.Size() == 3);

	cout << "PASSED!" << endl << endl;
}

void TestLargeTreeAndInvariants(){
	vector<int> values(1000);
	for (int i = 0; i < 1000; ++i) values[i] = i;
	shuffle(values.begin(), values.end(), mt19937(12345));

	RedBlackTree rbt;
	for (int value : values) rbt.Insert(value);
	assert(rbt.Size() == 1000);
	assert(rbt.GetMin() == 0 && rbt.GetMax() == 999);
	for (int value : values) assert(rbt.Contains(value));
	assert(!rbt.Contains(-1) && !rbt.Contains(1000));
	assert(rbt.root != nullptr && rbt.root->color == COLOR_BLACK);

	auto check = [&](auto&& self, RBTNode* node, int lower, int upper) -> int {
		if (node == nullptr) return 1;
		assert(lower < node->value && node->value < upper);
		assert(node->color == COLOR_RED || node->color == COLOR_BLACK);
		if (node->left != nullptr) assert(node->left->parent == node);
		if (node->right != nullptr) assert(node->right->parent == node);
		if (node->color == COLOR_RED) {
			assert(node->left == nullptr || node->left->color == COLOR_BLACK);
			assert(node->right == nullptr || node->right->color == COLOR_BLACK);
		}
		int left = self(self, node->left, lower, node->value);
		int right = self(self, node->right, node->value, upper);
		assert(left == right);
		return left + (node->color == COLOR_BLACK);
	};
	check(check, rbt.root, -1, 1000);
}





int main(){

	
	TestSimpleConstructor();
	TestConstructor();
	
	TestInsertFirstNode();
	TestInsertSecondNode();
	TestInsertThirdNode();
	TestInsertFourthNode();
	TestInsertFifthNode();
	TestDuplicateInsert();

	TestToStrings();
	TestInsertRandomTests();

	TestCopyConstructor();

	TestContains();
	TestGetMinimumMaximum();
	TestSize();
	TestLargeTreeAndInvariants();

	
	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}
