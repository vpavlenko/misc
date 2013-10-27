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
};


Node *root = NULL;


Node *create_node(int value) {
    Node *node = new Node();
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->size = 1;
    node->height = rand();
    return node;
}

void recalc(Node *node) {
    node->size = (node->left ? node->left->size : 0) + 
                 (node->right ? node->right->size : 0) + 1;
}

Node *merge(Node *left, Node *right) {
    if (right == NULL) {
        return left;
    } else if (left == NULL) {
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

pair<Node *, Node *> split(Node *node, int value) {
    // [ .. value), [value .. )
    if (node == NULL) {
        return make_pair<Node *, Node *>(NULL, NULL);
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

int _next(int number) {
    pair<Node *, Node *> root_splitted = split(root, number);
    int retval;

    if (root_splitted.second == NULL) {
        retval = -1;
    } else {
        Node *pred = root_splitted.second;
        while (pred->left != NULL) {
            pred = pred->left;
        }
        retval = pred->value;
    }

    root = merge(root_splitted.first, root_splitted.second);
    return retval;
}

void add(int number) {
    if (_next(number) != number) {
        Node *new_node = create_node(number);
        pair<Node *, Node *> parts = split(root, number);
        root = merge(merge(parts.first, new_node), parts.second);
    }
}

int main() {
    int n;
    ifstream cin("input.txt");
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string command;
        int number, y;

        cin >> command >> number;
        if (command == "+") {
            add((number + y) % 1000000000);
            y = 0;
        } else {
            y = _next(number);
            cout << y << endl;
        }
    }

    return 0;
}