//В начале решал не ту задачу. Думал нужно найти длинейшую строку чисел, в которой не более трёх одинаковых
#include <iostream>
#include <vector>

int main() {
    int size;
    std::cin >> size;
    int start = 0;
    int stop = 0;
    int sizeOfLine = 0;
    int startMax = 0;
    int stopMax = 0;
    int maxSizeOfLine = 0;
    int flower = -1, count = 1;

    for (int i = 0; i < size; ++i) {
        int num = -1;
        std::cin >> num;
        if (flower == num) {
            count++;
            if (count >= 3) {
                start = stop;
                stop = i - 1;
                sizeOfLine = stop - start + 1;
                if (sizeOfLine > maxSizeOfLine) {
                    startMax = start;
                    stopMax = stop;
                    maxSizeOfLine = stopMax - startMax + 1;
                }
            }
        } else {
            flower = num;
            count = 1;
        }
    }

    // Checking tail of set
    start = stop;
    stop = size - 1;
    sizeOfLine = stop - start + 1;
    if (sizeOfLine > maxSizeOfLine) {
        startMax = start;
        stopMax = stop;
    }

    printf("%d %d", startMax + 1, stopMax + 1);

    return 0;
}
