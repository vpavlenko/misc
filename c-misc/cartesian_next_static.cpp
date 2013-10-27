#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <cstdlib>

using namespace std;


const int MAXN = 500000;


struct Node {
    int value;
    int height;
    int size;
    int left, right;
};

Node nodes[MAXN];
int free_node = 0;
int root = -1;


int create_node(int value) {
    nodes[free_node].value = value;
    nodes[free_node].left = -1;
    nodes[free_node].right = -1;
    nodes[free_node].size = 1;
    nodes[free_node].height = rand();
    return free_node++;
}

void recalc(int node) {
    nodes[node].size = (nodes[node].left != -1 ? nodes[nodes[node].left].size : 0) + 
                       (nodes[node].right != -1 ? nodes[nodes[node].right].size : 0) + 1;
}

int merge(int left, int right) {
    if (right == -1) {
        return left;
    } else if (left == -1) {
        return right;
    } else {
        if (nodes[left].height < nodes[right].height) {
            nodes[right].left = merge(left, nodes[right].left);
            recalc(right);

            return right;
        } else {
            nodes[left].right = merge(nodes[left].right, right);
            recalc(left);

            return left;
        }
    }
}

pair<int, int> split(int node, int value) {
    // [ .. value), [value .. )
    if (node == -1) {
        return make_pair(-1, -1);
    }

    if (nodes[node].value < value) {
        pair<int, int> right_splitted = split(nodes[node].right, value);
        nodes[node].right = right_splitted.first;
        recalc(node);

        return make_pair(node, right_splitted.second);
    } else {
        pair<int, int> left_splitted = split(nodes[node].left, value);
        nodes[node].left = left_splitted.second;
        recalc(node);

        return make_pair(left_splitted.first, node);
    }
}

int _next(int number) {
    pair<int, int> root_splitted = split(root, number);
    int retval;

    if (root_splitted.second == -1) {
        retval = -1;
    } else {
        int pred = root_splitted.second;
        while (nodes[pred].left != -1) {
            pred = nodes[pred].left;
        }
        retval = nodes[pred].value;
    }

    root = merge(root_splitted.first, root_splitted.second);
    return retval;
}

void add(int number) {
    if (_next(number) != number) {
        int new_node = create_node(number);
        pair<int, int> parts = split(root, number);
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