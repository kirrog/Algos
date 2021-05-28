#include <iostream>
#include <vector>
#include <list>

using namespace std;

struct Node {
    list<Node *> nodes;
    int key = -1;
    bool checked = false;
};

void checkChain(Node *iter) {
    for (auto &&node :iter->nodes) {
        if (node->checked) {
            continue;
        } else {
            node->checked = true;
            checkChain(node);
        }
    }
}

int main() {
    int size;
    cin >> size;

    vector<Node> moneyBoxes(size);

    for (int i = 0; i < size; ++i) {
        int num = 0;
        cin >> num;
        num--;
        moneyBoxes[i].key = num;
        moneyBoxes[num].nodes.push_front(&moneyBoxes[i]);
    }

    int res = 0;

    for (int i = 0; i < size; ++i) {
        if (moneyBoxes[i].nodes.empty() && !moneyBoxes[i].checked) {
            res++;
            moneyBoxes[i].checked = true;
            Node *iter = &moneyBoxes[i];
            while (!moneyBoxes[iter->key].checked) {
                moneyBoxes[iter->key].checked = true;
                checkChain(iter);
                iter = &moneyBoxes[iter->key];
            }
            checkChain(iter);
        }
    }

    for (int i = 0; i < size; ++i) {
        if (!moneyBoxes[i].checked) {
            res++;
            moneyBoxes[i].checked = true;
            Node *iter = &moneyBoxes[i];
            while (!moneyBoxes[iter->key].checked) {
                moneyBoxes[iter->key].checked = true;
                iter = &moneyBoxes[iter->key];
            }
        }
    }

    printf("%d", res);

    return 0;
}
