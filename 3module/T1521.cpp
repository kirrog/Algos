

#include <iostream>
#include <vector>

using namespace std;

struct CustomNode {

    int val;

    CustomNode *next;
    CustomNode *prev;

    CustomNode(){

    }

    CustomNode(int val, CustomNode *next, CustomNode *prev) {
        this->val = val;
        this->next = next;
        this->prev = prev;
    }

    void del(){
        prev->next = next;
        next->prev = prev;
    }

};

int main() {
    int solders;
    cin >> solders;
    int number;
    cin >> number;

    vector<CustomNode> deque(solders);

    for (int i = solders; i > 0; --i) {
        deque[i - 1].val = i;
        if (i == 1) {
            deque[i - 1].prev = &deque[solders - 1];
        } else {
            deque[i - 1].prev = &deque[i - 2];
        }
        if (i == solders) {
            deque[i - 1].next = &deque[0];
        } else {
            deque[i - 1].next = &deque[i];
        }
    }

    CustomNode *iter = &deque[0];
    int num = 1;

    while (iter->next != iter) {
        if (num == number) {
            printf("%d ", iter->val);
            num = 1;
            iter->del();
        } else {
            num++;
        }
        iter = iter->next;
    }

    printf("%d ", iter->val);



}