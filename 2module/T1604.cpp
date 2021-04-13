

#include <iostream>
#include <vector>
#include <deque>


int compare(std::pair<int, int> fir, std::pair<int, int> sec) {
    if (fir.second > sec.second) {
        return 1;
    } else if (fir.second < sec.second) {
        return -1;
    } else if (fir.second == sec.second) {
        return 0;
    }
}

void sortVector(std::vector<std::pair<int, int>> *pVector, int firstElement, int lastElement) {

    if (lastElement - firstElement == 0) {
        return;
    } else if (lastElement - firstElement == 1) {
        if (compare((*pVector)[firstElement], (*pVector)[lastElement]) < 0) {
            std::pair<int, int> i = (*pVector)[firstElement];
            (*pVector)[firstElement] = (*pVector)[lastElement];
            (*pVector)[lastElement] = i;
        }
    } else {

        int middleIter = (firstElement + (lastElement - firstElement) / 2) + 1;

        sortVector(pVector, firstElement, middleIter - 1);
        sortVector(pVector, middleIter, lastElement);

        int firstIter = firstElement;

        int secondIter = middleIter;

        std::vector<std::pair<int, int>> middleInts(lastElement - firstElement + 1);

        for (int i = 0; i <= lastElement - firstElement; ++i) {
            if (compare((*pVector)[firstIter], (*pVector)[secondIter]) >= 1) {
                middleInts[i] = (*pVector)[firstIter++];
                if (firstIter == middleIter) {
                    for (int j = i + 1; j <= lastElement - firstElement; ++j) {
                        middleInts[j] = (*pVector)[secondIter++];
                    }
                    break;
                }
            } else {
                middleInts[i] = (*pVector)[secondIter++];
                if (secondIter == lastElement + 1) {
                    for (int j = i + 1; j <= lastElement - firstElement; ++j) {
                        middleInts[j] = (*pVector)[firstIter++];
                    }
                    break;
                }
            }
        }

        for (int i = 0; i <= lastElement - firstElement; ++i) {
            (*pVector)[firstElement + i] = middleInts[i];
        }
    }
}

void resortChangedDeque(std::deque<std::pair<int, int>> *pairs, int *size) {
    //Первый выбыл, пересорт последовательно
    if (pairs->back().second == 0) {
        pairs->pop_back();
        (*size)--;
        if((*size) == 0){
            return;
        }
    }
    if (pairs->front().second == 0) {
        pairs->pop_front();
        (*size)--;
    } else {

        for (int i = 0; i < (*size) - 1; ++i) {
            if (pairs->at(i).second >= pairs->at(i + 1).second) {
                break;
            } else {
                std::pair<int, int> middle = pairs->at(i);
                pairs->at(i) = pairs->at(i + 1);
                pairs->at(i + 1) = middle;
            }
        }

    }
}

int main() {

    int signsNum;
    std::cin >> signsNum;
    std::vector<std::pair<int, int>> signs(signsNum);
    int acum = 0;
    for (int i = 0; i < signsNum; ++i) {
        double num;
        std::cin >> num;
        acum += num;
        signs[i].first = i + 1;
        signs[i].second = num;
    }

    sortVector(&signs, 0, signsNum - 1);

    std::deque<std::pair<int, int>> pairsWork;

    for (int i = 0; i < signsNum; ++i) {
        pairsWork.push_back(signs[i]);
    }

    for (int i = 0; i < acum;) {

        if (pairsWork.front().second > 0) {
            printf("%d ", pairsWork.front().first);
            pairsWork.front().second--;
            ++i;
        }
        if (pairsWork.back().second > 0) {
            printf("%d ", pairsWork.back().first);
            pairsWork.back().second--;
            ++i;
        }

        resortChangedDeque(&pairsWork, &signsNum);
    }

}