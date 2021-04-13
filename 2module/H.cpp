

#include <iostream>
#include <vector>


int compare(int fir, int sec) {
    if (fir > sec) {
        return 1;
    } else if (fir < sec) {
        return -1;
    } else if (fir == sec) {
        return 0;
    }
}

void sortVector(std::vector<int> *ints, int firstElement, int lastElement) {

    if (lastElement - firstElement == 0) {
        return;
    } else if (lastElement - firstElement == 1) {
        if (compare((*ints)[firstElement], (*ints)[lastElement]) < 0) {
            int i = (*ints)[firstElement];
            (*ints)[firstElement] = (*ints)[lastElement];
            (*ints)[lastElement] = i;
        }
    } else {

        int middleIter = (firstElement + (lastElement - firstElement) / 2) + 1;

        sortVector(ints, firstElement, middleIter - 1);
        sortVector(ints, middleIter, lastElement);

        int firstIter = firstElement;

        int secondIter = middleIter;

        std::vector<int> middleInts(lastElement - firstElement + 1);

        for (int i = 0; i <= lastElement - firstElement; ++i) {
            if (compare((*ints)[firstIter], (*ints)[secondIter]) >= 1) {
                middleInts[i] = (*ints)[firstIter++];
                if (firstIter == middleIter) {
                    for (int j = i + 1; j <= lastElement - firstElement; ++j) {
                        middleInts[j] = (*ints)[secondIter++];
                    }
                    break;
                }
            } else {
                middleInts[i] = (*ints)[secondIter++];
                if (secondIter == lastElement + 1) {
                    for (int j = i + 1; j <= lastElement - firstElement; ++j) {
                        middleInts[j] = (*ints)[firstIter++];
                    }
                    break;
                }
            }
        }

        for (int i = 0; i <= lastElement - firstElement; ++i) {
            (*ints)[firstElement + i] = middleInts[i];
        }
    }
}

int main() {

    int item;
    std::cin >> item;
    int ord;
    std::cin >> ord;

    std::vector<int> orders(item);
    for (int i = 0; i < (int) item; ++i) {
        std::cin >> orders[i];
    }

    sortVector(&orders, 0, orders.size() - 1);

    int acum = 0;

    for (int i = 0; i < item; ++i) {
        if ((i+1) % (ord) != 0) {
            acum += orders[i];
        }
    }

    printf("%d", acum);

    return 0;
}