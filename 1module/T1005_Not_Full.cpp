
#include "iostream"
#include <algorithm>
#include <vector>

int main() {

    int size;
    std::cin >> size;
    std::vector<int> vector(size,0);
    for (int i = 0; i < size; ++i) {
        std::cin >> vector[i];
    }
    std::sort(vector.begin(), vector.end(), std::greater<int>());

    int difference = 0;
    for (int i = 0; i < size; ++i) {
        if (difference > 0) {
            difference -= vector[i];
        } else {
            difference += vector[i];
        }
    }

    int prev = vector[0];
    std::vector<int> differ(size - 1, 0);
    int delay = 0;
    for (int i = 1; i < size; ++i) {
        if (prev != vector[i]) {
            differ[i-delay-1] = prev - vector[i];
            prev = vector[i];
        } else {
            delay++;
        }
    }
    std::sort(differ.begin(), differ.end() - delay);

    bool cycle = true;
    while (cycle) {
        if (difference == 0) {
            cycle = false;
            break;
        }
        for (int i = 0; i < size - delay; ++i) {
            if (differ[i] > difference) {
                if (i == 0) {
                    cycle = false;
                    break;
                }
                difference -= differ[i - 1];
                differ.erase(differ.begin() + i - 1);
                break;
            } else {
                if (i == size - delay - 1) {
                    difference -= differ[i];
                    differ.erase(differ.begin() + i);
                }
            }
        }

    }

    if (difference >= 0) {
        printf("%d", difference);
    } else {
        printf("%d", -difference);
    }
    return 0;
}