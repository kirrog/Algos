#include <iostream>
#include <vector>
#include <algorithm>

int factorial(int n) {
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

int perestCNK(int n, int k) {
    return factorial(n) / ((factorial(k)) * (factorial(n - k)));
}

int main() {
    int pos;
    std::cin >> pos;
    int cow;
    std::cin >> cow;
    std::vector<int> positions(pos);
    for (int i = 0; i < (int) pos; ++i) {
        std::cin >> positions[i];
    }
    int max = 0;
    int iterations = factorial(pos - 1) / ((factorial(cow - 1)) * (factorial(pos - cow)));

    for (int i = 0; i < iterations; ++i) {
        std::vector<int> arrBool(pos - 1, 0);
        int prevCow = 1;
        for (int j = 0; j < pos - 1; ++j) {
            if (i <= perestCNK(pos - 1 - j, cow - prevCow)) {
                arrBool[j] = 1;
                prevCow++;
                if (prevCow == cow) {
                    for (int k = j + 1; k < pos - 1; ++k) {
                        arrBool[k] = 0;
                    }
                    break;
                }
            } else {
                arrBool[j] = false;
            }
        }

        int min = positions[positions.size() - 1] - positions[0];

        prevCow = 0;
        for (int j = 0; j < pos - 1; ++j) {
            if (arrBool[j] != 0) {
                min = std::min(min, (positions[j + 1] - positions[prevCow]));
            }
        }

        max = std::max(max, min);
    }

    printf("%d", max);

    return 0;
}