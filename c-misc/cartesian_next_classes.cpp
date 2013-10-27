#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <cstdlib>

using namespace std;

struct Node {
    int value;
    int height;
    int size;
    Node *left, *right;

    // constructor for the dummy node
    Node() {
        size = 0;
        left = this;
        right = this;
    }

    Node(int);
};

Node *DUMMY = new Node();

Node::Node(int value) : value(value), height(rand()), size(1), 
                        left(DUMMY), right(DUMMY) {}

class CartesianTree {
private:
    Node *root;
    
    void recalc(Node *node);
    Node *merge(Node *left, Node *right);
    pair<Node *, Node *> split(Node *node, int value);

public:
    CartesianTree() : root(DUMMY) {}

    int next(int number);
    void add(int number);
};

void CartesianTree::recalc(Node *node) {
    node->size = node->left->size + node->right->size;
}

Node *CartesianTree::merge(Node *left, Node *right) {
    if (right == DUMMY) {
        return left;
    } else if (left == DUMMY) {
        return right;
    } else {
        if (left->height < right->height) {
            right->left = merge(left, right->left);
            recalc(right);

            return right;
        } else {
            left->right = merge(left->right, right);
            recalc(left);

            return left;
        }
    }
}

pair<Node *, Node *> CartesianTree::split(Node *node, int value) {
    // [ .. value), [value .. )
    if (node == DUMMY) {
        return make_pair(DUMMY, DUMMY);
    }

    if (node->value < value) {
        pair<Node *, Node *> right_splitted = split(node->right, value);
        node->right = right_splitted.first;
        recalc(node);

        return make_pair(node, right_splitted.second);
    } else {
        pair<Node *, Node *> left_splitted = split(node->left, value);
        node->left = left_splitted.second;
        recalc(node);

        return make_pair(left_splitted.first, node);
    }
}

int CartesianTree::next(int number) {
    pair<Node *, Node *> root_splitted = split(root, number);
    int retval;

    if (root_splitted.second == DUMMY) {
        retval = -1;
    } else {
        Node *pred = root_splitted.second;
        while (pred->left != DUMMY) {
            pred = pred->left;
        }
        retval = pred->value;
    }

    root = merge(root_splitted.first, root_splitted.second);
    return retval;
}

void CartesianTree::add(int number) {
    if (next(number) != number) {
        Node *new_node = new Node(number);
        pair<Node *, Node *> parts = split(root, number);
        root = merge(merge(parts.first, new_node), parts.second);
    }
}

int main() {
    int n;
    ifstream cin("input.txt");
    cin >> n;

    CartesianTree ct;

    for (int i = 0; i < n; ++i) {
        string command;
        int number, y;

        cin >> command >> number;
        if (command == "+") {
            ct.add((number + y) % 1000000000);
            y = 0;
        } else {
            y = ct.next(number);
            cout << y << endl;
        }
    }

    return 0;
}