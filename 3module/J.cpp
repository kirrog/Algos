
#include <iostream>
#include <deque>
#include <string>

using namespace std;

int main() {
    int gobOrdNum;
    cin >> gobOrdNum;

    deque<int> goblins;

    auto iter = goblins.begin(); // use this iterator for vip goblins

    int size = 0;

    for (int i = 0; i < gobOrdNum; ++i) {
        string sign;
        cin >> sign;
        switch (sign.at(0)) {
            case '+': {
                cin >> sign;
                int num = stoi(sign);

                goblins.push_front(num);
                size++;

                if (size == 1) {
                    iter = goblins.begin();
                }

                if (size % 2 == 0 && size > 2) {
                    iter--;
                }

                break;
            }
            case '*': {
                cin >> sign;
                int num = stoi(sign);

                if (size == 0) {
                    goblins.push_front(num);
                    size++;
                    iter = goblins.begin();
                } else {
                    goblins.insert(iter, num);
                    size++;

                    if (size % 2 == 1 && size > 2) {
                        iter++;
                    }

                }

                break;
            }
            case '-': {
                size--;
                int res = goblins.at(size);
                goblins.pop_back();
                printf("%d\n", res);

                if (size == 1) {
                    iter = goblins.begin();
                } else {
                    if (size % 2 == 0) {
                        iter--;
                    }
                }

                break;
            }
            default: {
                break;
            }
        }
        printf("\n -- \n");
        for (int j = 0; j < size; ++j) {
            printf("%d ", goblins.at(j));
        }
        printf("\n --");

    }

    return 0;
}
