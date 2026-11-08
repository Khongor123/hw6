#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <string>

#define COLOR_RED 0
#define COLOR_BLACK 1
#define COLOR_DOUBLE_BLACK 2

struct RBTNode {
    int value;
    int color;
    RBTNode *left = nullptr;
    RBTNode *right = nullptr;
    RBTNode *parent = nullptr;
};

class RedBlackTree {
public:
    RedBlackTree();
    explicit RedBlackTree(int value);
    RedBlackTree(const RedBlackTree &other);

    void Insert(int value);
    bool Contains(int value) const;
    int GetMin() const;
    int GetMax() const;
    unsigned long long int Size() const;

    std::string ToInfixString() const { return ToInfixString(root); }
    std::string ToPrefixString() const { return ToPrefixString(root); }
    std::string ToPostfixString() const { return ToPostfixString(root); }

private:
    friend void TestLargeTreeAndInvariants();
    static RBTNode *CloneSubtree(const RBTNode *n, RBTNode *parent);

    void RotateLeft(RBTNode *n);
    void RotateRight(RBTNode *n);
    void FixInsert(RBTNode *n);

    std::string ToInfixString(RBTNode *n) const;
    std::string ToPrefixString(RBTNode *n) const;
    std::string ToPostfixString(RBTNode *n) const;

    unsigned long long int numItems = 0;
    RBTNode *root = nullptr;
};

#endif
