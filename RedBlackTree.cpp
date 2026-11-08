#include "RedBlackTree.h"

#include <stdexcept>

RedBlackTree::RedBlackTree() = default;

RedBlackTree::RedBlackTree(int value) {
    Insert(value);
}

RedBlackTree::RedBlackTree(const RedBlackTree &other)
    : numItems(other.numItems), root(CloneSubtree(other.root, nullptr)) {}

RBTNode *RedBlackTree::CloneSubtree(const RBTNode *n, RBTNode *parent) {
    if (n == nullptr) {
        return nullptr;
    }

    // keep copies independent.
    RBTNode *copy = new RBTNode{n->value, n->color};
    copy->parent = parent;
    copy->left = CloneSubtree(n->left, copy);
    copy->right = CloneSubtree(n->right, copy);
    return copy;
}

void RedBlackTree::Insert(int value) {
    // the root must be black.
    if (root == nullptr) {
        root = new RBTNode{value, COLOR_BLACK};
        ++numItems;
        return;
    }

    RBTNode *parent = nullptr;
    RBTNode *current = root;
    while (current != nullptr) {
        parent = current;
        if (value == current->value) {
            throw std::invalid_argument("duplicates are not allowed");
        }
        current = value < current->value ? current->left : current->right;
    }

    RBTNode *node = new RBTNode{value, COLOR_RED};
    node->parent = parent;
    if (value < parent->value) {
        parent->left = node;
    } else {
        parent->right = node;
    }
    ++numItems;
    FixInsert(node);
}

bool RedBlackTree::Contains(int value) const {
    const RBTNode *current = root;
    while (current != nullptr) {
        if (value == current->value) {
            return true;
        }
        current = value < current->value ? current->left : current->right;
    }
    return false;
}

int RedBlackTree::GetMin() const {
    if (root == nullptr) {
        throw std::out_of_range("Cannot get the minimum of an empty tree");
    }

    const RBTNode *current = root;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current->value;
}

int RedBlackTree::GetMax() const {
    if (root == nullptr) {
        throw std::out_of_range("Cannot get the maximum of an empty tree");
    }

    const RBTNode *current = root;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current->value;
}

unsigned long long int RedBlackTree::Size() const {
    return numItems;
}

void RedBlackTree::RotateLeft(RBTNode *n) {
    RBTNode *pivot = n->right;
    n->right = pivot->left;
    if (pivot->left != nullptr) {
        pivot->left->parent = n;
    }

    pivot->parent = n->parent;
    if (n->parent == nullptr) {
        root = pivot;
    } else if (n == n->parent->left) {
        n->parent->left = pivot;
    } else {
        n->parent->right = pivot;
    }

    pivot->left = n;
    n->parent = pivot;
}

void RedBlackTree::RotateRight(RBTNode *n) {
    RBTNode *pivot = n->left;
    n->left = pivot->right;
    if (pivot->right != nullptr) {
        pivot->right->parent = n;
    }

    pivot->parent = n->parent;
    if (n->parent == nullptr) {
        root = pivot;
    } else if (n == n->parent->left) {
        n->parent->left = pivot;
    } else {
        n->parent->right = pivot;
    }

    pivot->right = n;
    n->parent = pivot;
}

void RedBlackTree::FixInsert(RBTNode *n) {
    while (n->parent != nullptr && n->parent->color == COLOR_RED) {
        RBTNode *grandparent = n->parent->parent;
        if (n->parent == grandparent->left) {
            RBTNode *uncle = grandparent->right;
            if (uncle != nullptr && uncle->color == COLOR_RED) {
                // move the red conflict upward.
                n->parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                n = grandparent;
            } else {
                if (n == n->parent->right) {
                    // convert left-right to left-left.
                    n = n->parent;
                    RotateLeft(n);
                }
                n->parent->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                RotateRight(grandparent);
            }
        } else {
            RBTNode *uncle = grandparent->left;
            if (uncle != nullptr && uncle->color == COLOR_RED) {
                n->parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                n = grandparent;
            } else {
                if (n == n->parent->left) {
                    // convert right-left to right-right.
                    n = n->parent;
                    RotateRight(n);
                }
                n->parent->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                RotateLeft(grandparent);
            }
        }
    }

    // keep the root black after recoloring.
    root->color = COLOR_BLACK;
}

std::string RedBlackTree::ToInfixString(RBTNode *n) const {
    if (n == nullptr) {
        return "";
    }

    const char color = n->color == COLOR_RED ? 'R' : 'B';
    return ToInfixString(n->left) + " " + color +
           std::to_string(n->value) + " " + ToInfixString(n->right);
}

std::string RedBlackTree::ToPrefixString(RBTNode *n) const {
    if (n == nullptr) {
        return "";
    }

    const char color = n->color == COLOR_RED ? 'R' : 'B';
    return std::string(" ") + color + std::to_string(n->value) + " " +
           ToPrefixString(n->left) + ToPrefixString(n->right);
}

std::string RedBlackTree::ToPostfixString(RBTNode *n) const {
    if (n == nullptr) {
        return "";
    }

    const char color = n->color == COLOR_RED ? 'R' : 'B';
    return ToPostfixString(n->left) + ToPostfixString(n->right) +
           " " + color + std::to_string(n->value) + " ";
}
