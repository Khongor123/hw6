#include "RedBlackTree.h"

#include <stdexcept>

RedBlackTree::RedBlackTree() = default;

RedBlackTree::RedBlackTree(int value) {
    Insert(value);
}

void RedBlackTree::Insert(int value) {
    // The first node is the root, which must always be black.
    if (root == nullptr) {
        root = new RBTNode{value, COLOR_BLACK};
        ++numItems;
        return;
    }

    // Insertion below a root and rebalancing are the next implementation step.
    throw std::logic_error("Insertion into a nonempty tree is not implemented yet");
}

std::string RedBlackTree::ToInfixString(RBTNode *n) const {
    if (n == nullptr) {
        return "";
    }

    const char color = n->color == COLOR_RED ? 'R' : 'B';
    return ToInfixString(n->left) + " " + color +
           std::to_string(n->value) + " " + ToInfixString(n->right);
}
