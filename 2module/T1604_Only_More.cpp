
#include <iostream>
#include <vector>


int compare(std::pair<int, int> fir, std::pair<int, int> sec) {
    if (fir.second > sec.second) {
        return 1;
    } else if (fir.second < sec.second) {
        return -1;
    } else if (fir.second == sec.second) {
        return 0;
    }
}

void sortVector(std::vector<std::pair<int, int>> *ints, int firstElement, int lastElement) {

    if (lastElement - firstElement == 0) {
        return;
    } else if (lastElement - firstElement == 1) {
        if (compare((*ints)[firstElement], (*ints)[lastElement]) < 0) {
            std::pair<int, int> i = (*ints)[firstElement];
            (*ints)[firstElement] = (*ints)[lastElement];
            (*ints)[lastElement] = i;
        }
    } else {

        int middleIter = (firstElement + (lastElement - firstElement) / 2) + 1;

        sortVector(ints, firstElement, middleIter - 1);
        sortVector(ints, middleIter, lastElement);

        int firstIter = firstElement;

        int secondIter = middleIter;

        std::vector<std::pair<int, int>> middleInts(lastElement - firstElement + 1);

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

    int signsNum;
    std::cin >> signsNum;
    std::vector<std::pair<int, int>> signs(signsNum);
    for (int i = 0; i < signsNum; ++i) {
        double num;
        std::cin >> num;
        signs[i].first = i + 1;
        signs[i].second = num;
    }

    sortVector(&signs, 0, signsNum - 1);

    for (int i = 0; i < signsNum; ++i) {
        if (signs[i].second > 0) {
            printf("%d ", signs[i].first);
            int size = signs[i].second;
            signs[i].second = 0;
            size--;
            int signNumber = i + 1;
            int quantity = 0;

            for (int j = 1; j <= size; ++j) {

                if (signNumber < signsNum && quantity == 0) {
                    while (signNumber < signsNum && signs[signNumber].second == 0) {
                        signNumber++;
                    }
                    if (signNumber < signsNum) {
                        quantity = signs[signNumber].second;
                        signs[signNumber].second = 0;
                    }
                }
                if (quantity > 0) {
                    printf("%d ", signs[signNumber].first);
                    quantity--;
                }
                printf("%d ", signs[i].first);
            }

            if (quantity != 0) {
                signs[signNumber].second = quantity;
            }

        }
    }

    return 0;
}