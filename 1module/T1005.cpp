//313607NJ - KR
//313875AL - VTALGOKR


#include "iostream"
#include <algorithm>
#include <vector>

int calculateSum(std::vector<int> * vec,
                 int sum,
                 int step,
                 int limit,
                 int prevAccum,
                 bool plus) {

    if (plus) {
        prevAccum += (*vec)[step];
    }

    if (step == limit - 1) {
        return sum - 2 * prevAccum;
    } else {
        int left = calculateSum(vec, sum, step + 1, limit, prevAccum, true);
        int right = calculateSum(vec, sum, step + 1, limit, prevAccum, false);

        return std::min(abs(left), abs(right));
    }
}

int main() {

    int size;
    std::cin >> size;
    std::vector<int> vector(size, 0);
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        std::cin >> vector[i];
        sum += vector[i];
    }

    int left = calculateSum(&vector, sum, 0, size, 0, true);
    int right = calculateSum(&vector, sum, 0, size, 0, false);

    int difference = std::min(abs(left), abs(right));

    if (difference >= 0) {
        printf("%d", difference);
    } else {
        printf("%d", -difference);
    }
    return 0;
}