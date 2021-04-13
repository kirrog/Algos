
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int size;
    std::cin >> size;
    if (size == 0) {
        printf("%d", 0);
        return 0;
    }
    std::vector<int> vector(size, 0);
    int changedSize = 0;
    int acum;
    std::cin >> acum;
    bool sign = acum >= 0;
    for (int i = 1; i < size; ++i) {
        int a;
        std::cin >> a;
        if (sign == a >= 0) {
            acum += a;
        } else {
            vector[changedSize++] = acum;
            acum = a;
            sign = a >= 0;
        }
    }
    vector[changedSize++] = acum;

//    int max = vector[0],
//            sum = 0;
//    for (int r = 0; r < changedSize; r++) {
//        sum += vector[r];
//        max = std::max(max, sum);
//        sum = std::max(sum, 0);
//    }

    int ans = vector[0],
            sum = 0,
            min_sum = 0;
    for (int r = 0; r < vector.size(); ++r) {
        sum += vector[r];
        ans = std::max(ans, sum - min_sum);
        min_sum = std::min(min_sum, sum);
    }
    printf("%d", ans);

    return 0;
}