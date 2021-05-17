

#include <iostream>
#include <vector>

using namespace std;

struct CustomNode {

    int val;

    CustomNode *next;
    CustomNode *prev;

    CustomNode() {

    }

    CustomNode(int val, CustomNode *next, CustomNode *prev) {
        this->val = val;
        this->next = next;
        this->prev = prev;
    }

    void del() {
        prev->next = next;
        next->prev = prev;
    }

};

int powerOfNumber(int num) {
    int size = num;
    int pow = 0;
    while (size > 0) {
        size = size >> 1;
        pow++;
    }
    if (num << 1 == 1 << pow) {
        pow--;
    }
    return pow;
}

struct CustomTree {

    vector<int> tree;
    int heapSize;

    int parent(int num) {
        if (num <= 0) {
            return 0;
        }
        return (num - 1) / 2;
    }

    int left(int num) {
        int res = 2 * num + 1;
        if (res >= tree.size()) {
            return tree.size() - 1;
        } else {
            return res;
        }
    }

    int right(int num) {
        int res = 2 * num + 2;
        if (res >= tree.size()) {
            return tree.size() - 1;
        } else {
            return res;
        }
    }

    CustomTree(vector<int> &data) {
        int coordSize = (1 << powerOfNumber(data.size())) - 1;
        heapSize = coordSize;

        tree.resize(data.size() + coordSize);

        for (int i = 0; i < data.size(); ++i) {
            int pos = i + coordSize;
            tree[pos] = data[i] + 1;
            pos = parent(pos);
            while (pos) {
                tree[pos]++;
                pos = parent(pos);
            }
        }
        tree[0] = data.size();
    }

    int getNumber(int pos, int treeRoot) {
        int res = 0;
        if (pos == 0) {
            res = tree[treeRoot];
            tree[treeRoot] = 0;
            while (parent(treeRoot) > 0) {
                treeRoot = parent(treeRoot);
                tree[treeRoot]--;
            }
            tree[0]--;
        } else {
            int leftSize;
            if (left(treeRoot) < heapSize) {
                leftSize = tree[left(treeRoot)];
            } else {
                if (pos == 1) {
                    if (treeRoot >= heapSize) {
                        res = getNumber(0, treeRoot);
                    } else {
                        if (tree[left(treeRoot)] == 0) {
                            res = getNumber(0, right(treeRoot));
                        } else {
                            res = getNumber(0, left(treeRoot));
                        }
                    }
                } else if (pos == 2) {
                    if (treeRoot >= heapSize) {
                        res = getNumber(0, treeRoot);
                    } else {
                        res = getNumber(0, right(treeRoot));
                    }
                } else {
                    fprintf(stderr, "\nSheet happened\n");
                }
                return res;
            }
            if (leftSize < pos) {
                pos -= leftSize;
                treeRoot = right(treeRoot);
            } else {
                int l = left(treeRoot);
                if (tree[l] == 0) {
                    treeRoot = right(treeRoot);
                } else {
                    treeRoot = l;
                }
            }
            res = getNumber(pos, treeRoot);
        }
        return res;
    }

    int getNext(int &prev, int step) {
        int size = tree[0];
        prev += step - 1;
        while (prev > size) {
            prev -= size;
        }
        int result = getNumber(prev, 0);

        return result;
    }

    void printTree() {
        for (int i = 0; i < tree.size(); ++i) {
            printf("%d ", tree[i]);
        }
    }

};

int main() {
    int solders;
    cin >> solders;

    int number;
    cin >> number;

    vector<int> data(solders);

    for (int i = 0; i < solders; i++) {
        data[i] = i;
    }

    CustomTree *customTree = new CustomTree(data);

    int prev = 1;
    for (int i = 0; i < solders; i++) {
        int res = customTree->getNext(prev, number);
        //fprintf(stderr, "%d", prev);
        printf("%d ", res);
    }

    delete customTree;

}