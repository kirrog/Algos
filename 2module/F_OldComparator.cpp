
#include "iostream"
#include "string"
#include "vector"
#include "map"
#include "list"
#include "algorithm"

int compare(std::string fir, std::string sec) {

    int minSize = std::min(fir.size(), sec.size());
    for (int i = 0; i < minSize; ++i) {
        if (fir.at(i) == sec.at(i)) {//equals chars
            continue;
        } else {//unequal chars
            if (fir.at(i) > sec.at(i)) {
                return 1;
            } else {
                return -1;
            }
        }
    }
    if (fir.size() == sec.size()) {
        return 0;
    } else {
        if (fir.size() > sec.size()) {
            if (fir.at(minSize) > sec.at(0)) {
                return 1;
            } else{
                return -1;
            }
        } else {
            if (fir.at(0) < sec.at(minSize)) {
                return -1;
            } else{
                return 1;
            }
        }
    }
}

void sortedListFromVector(std::vector<std::string> *strs, int firstElement, int lastElement) {

    if (lastElement - firstElement == 0) {
        return;
    } else if (lastElement - firstElement == 1) {
        if (compare((*strs)[firstElement], (*strs)[lastElement]) < 0) {
            std::string string = (*strs)[firstElement];
            (*strs)[firstElement] = (*strs)[lastElement];
            (*strs)[lastElement] = string;
        }
    } else {

        int middleIter = (firstElement + (lastElement - firstElement) / 2) + 1;

        sortedListFromVector(strs, firstElement, middleIter - 1);
        sortedListFromVector(strs, middleIter, lastElement);

        int firstIter = firstElement;

        int secondIter = middleIter;

        std::vector<std::string> middleStrs(lastElement - firstElement + 1);

        for (int i = 0; i <= lastElement - firstElement; ++i) {
            if (compare((*strs)[firstIter], (*strs)[secondIter]) >= 1) {
                middleStrs[i] = (*strs)[firstIter++];
                if (firstIter == middleIter) {
                    for (int j = i + 1; j <= lastElement - firstElement; ++j) {
                        middleStrs[j] = (*strs)[secondIter++];
                    }
                    break;
                }
            } else {
                middleStrs[i] = (*strs)[secondIter++];
                if (secondIter == lastElement + 1) {
                    for (int j = i + 1; j <= lastElement - firstElement; ++j) {
                        middleStrs[j] = (*strs)[firstIter++];
                    }
                    break;
                }
            }
        }

        for (int i = 0; i <= lastElement - firstElement; ++i) {
            (*strs)[firstElement + i] = middleStrs[i];
        }
    }
}


int main() {
    std::list<std::string> strings;
    std::string str;

    while (std::cin >> str) {
        strings.push_front(str);
    }

    std::vector<std::string> strs(strings.size());
    int size = strings.size();
    for (int i = 0; i < size; ++i) {
        strs[i] = strings.front();
        strings.pop_front();
    }

    sortedListFromVector(&strs, 0, strs.size() - 1);
    for (const std::string &string : strs) {
        printf("%s\n", string.c_str());
    }

    return 0;

}
