
#include <map>
#include <vector>
#include <iostream>

using namespace std;

struct Node {
    int number;
    bool end = false;
    bool checked = false;
    vector<Node *> nodes;
};



void addNumber(vector<int> &number, vector<Node *> &vectorNode, vector<vector<int>> &weights, int num) {

}

void clearNode(Node *node) {
    if (!node->nodes.empty()) {
        for (auto &i : node->nodes) {
            clearNode(i);
        }
    }
    delete node;
}

void clearNodes(vector<Node *> &numbers) {
    for (int i = 0; i < numbers.size(); ++i) {
        clearNode(numbers[i]);
    }
}

int main() {
    vector<Node *> numbers(10);
    for (int i = 0; i < 10; ++i) {
        numbers[i] = new Node;
        numbers[i]->number = i;
    }
    int size;
    cin >> size;
    vector<int> number(10);

    vector<vector<int>> weights(size);
    for (int i = 0; i < size; ++i) {
        weights[i].reserve(size);
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < 10; ++j) {
            int r;
            cin >> r;
            number[j] = r - 48;
        }
        addNumber(number, numbers, weights, i);
    }

    printNodes(numbers);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%d ", weights[i][j]);
        }
        printf("\n");
    }

    clearNodes(numbers);
    return 0;
}