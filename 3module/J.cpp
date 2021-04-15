#include <iostream>
#include <deque>
#include <string>

using namespace std;

class CustomNode {
public:
    CustomNode *next;
    CustomNode *prev;
    int val;

    CustomNode(CustomNode *nextIn = nullptr,
               CustomNode *prevIn = nullptr,
               int valIn = 0) {
        next = nextIn;
        prev = prevIn;
        val = valIn;
    }
};

class CustomList {
public:
    CustomNode *head;
    CustomNode *tail;
    CustomNode *mid;

    int size;

    CustomList(CustomNode *headIn = nullptr,
               CustomNode *tailIn = nullptr,
               CustomNode *midIn = nullptr,
               int sizeIn = 0) {
        head = headIn;
        tail = tailIn;
        mid = midIn;
        size = sizeIn;
    }

};

void push_front(CustomList *customList, int val) {
    customList->size++;
    if (customList->head != nullptr) {
        auto custNode = new CustomNode(customList->head, nullptr, val);
        customList->head->prev = custNode;
        customList->head = custNode;
        if (customList->size % 2 == 1 && customList->size > 1) {
            if (customList->mid->prev != nullptr) {
                customList->mid = customList->mid->prev;
            }
        }
    } else {
        auto custNode = new CustomNode(nullptr, nullptr, val);
        customList->head = custNode;
        customList->mid = custNode;
        customList->tail = custNode;
    }
}

void push_mid(CustomList *customList, int val) {
    customList->size++;
    if (customList->mid == nullptr) {
        auto custNode = new CustomNode(nullptr, nullptr, val);
        customList->mid = custNode;
        customList->tail = custNode;
        customList->head = custNode;
    } else {
        auto custNode = new CustomNode(nullptr, nullptr, val);

        if ((customList->size) % 2 == 0 && customList->size > 1) {
            custNode->prev = customList->mid->prev;
            customList->mid->prev = custNode;
            custNode->next = customList->mid;
            if (custNode->prev != nullptr) {
                custNode->prev->next = custNode;
            } else {
                customList->head = custNode;
            }
        } else {
            custNode->prev = customList->mid->prev;
            custNode->next = customList->mid;
            customList->mid->prev = custNode;
            if (custNode->prev != nullptr) {
                custNode->prev->next = custNode;
            } else {
                customList->head = custNode;
            }
            customList->mid = custNode;
        }
    }
}

int pop_back(CustomList *customList) {

    customList->size--;
    int res = customList->tail->val;

    if (customList->size == 0) {
        customList->head = nullptr;
        customList->tail = nullptr;
        customList->mid = nullptr;
    } else {
        if (customList->size % 2 == 1) {
            customList->mid = customList->mid->prev;
        }

        customList->tail = customList->tail->prev;
        customList->tail->next = nullptr;
    }

    return res;

}

int main() {
    int gobOrdNum;
    cin >> gobOrdNum;

    auto *goblins = new CustomList();

    for (int i = 0; i < gobOrdNum; ++i) {
        string sign;
        cin >> sign;
        switch (sign.at(0)) {
            case '+': {
                string num;
                cin >> num;
                push_front(goblins, stoi(num));
                break;
            }
            case '*': {
                string num;
                cin >> num;
                push_mid(goblins, stoi(num));
                break;
            }
            case '-': {
                int res = pop_back(goblins);
                printf("%d\n", res);
                break;
            }
            default: {
                break;
            }
        }
    }

    return 0;
}
