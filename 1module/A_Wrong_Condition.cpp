#include <iostream>
#include <vector>

int main() {
    int size;
    std::cin >> size;
    int *array = (int *) malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        std::cin >> array[i];
    }
    int start = 0;
    int stop = 0;
    int sizeOfLine = 0;
    for (int i = 0; i < size; ++i) { // cycle trow all array
        bool hasLessThen3 = true;
        for (int j = i; hasLessThen3 && j < size; ++j) { // cycle trow elements of line
            int num = array[j];
            int count = 0;
            for (int k = j; k >= i; k--) { // cycle check line elements
                if (num == array[k]) {
                    count++;
                    if (count > 2) {
                        if (sizeOfLine < (j - i)) {
                            start = i;
                            stop = j - 1;
                            sizeOfLine = j - i;
                        }
                        hasLessThen3 = false;
                        break;
                    }
                }

            }
        }

        if (hasLessThen3 && sizeOfLine < (size - i)) {
            start = i;
            stop = size - 1;
            sizeOfLine = size - i;
        }

    }

    free(array);

    printf("%d %d", start + 1, stop + 1);

    return 0;
}

//В начале решал не ту задачу. Думал нужно найти длинейшую строку чисел, в которой не более трёх одинаковых