
#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Node {
    bool checked = false;
    bool color = false;
    set<Node *> neighbors;
};

bool paintNodes(vector<Node> &pupils, Node *iter, bool color) {
    iter->color = color;
    iter->checked = true;
    for (auto &&pup:iter->neighbors) {
        if (!pup->checked) {
            bool res = paintNodes(pupils, pup, !color);
            if (!res) {
                return res;
            }
        } else {
            if (pup->color == color) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int size;
    cin >> size;
    int pairs;
    cin >> pairs;

    vector<Node> pupils(size);

    for (int i = 0; i < pairs; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        pupils[l].neighbors.insert(&pupils[r]);
        pupils[r].neighbors.insert(&pupils[l]);
    }

    if (paintNodes(pupils, &pupils[0], true)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

//    for (int i = 0; i < size; ++i) {
//        printf("%d ", pupils[i].color);
//        for (auto &&neightbor:pupils[i].neighbors) {
//            printf("%d ", neightbor->color);
//        }
//        printf("\n");
//    }

}
