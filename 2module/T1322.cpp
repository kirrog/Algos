
#include <iostream>
#include <vector>

using namespace std;


int compare(pair<int, char> fir, pair<int, char> sec) {
    if (fir.second < sec.second) {
        return 1;
    } else if (fir.second > sec.second) {
        return -1;
    } else {
        if (fir.first < sec.first) {
            return 1;
        } else {
            return -1;
        }
    }
}

void sortString(vector<pair<int, char>> *string, int firstElement, int lastElement) {

    if (lastElement - firstElement == 0) {
        return;
    } else if (lastElement - firstElement == 1) {
        if (compare((*string)[firstElement], (*string)[lastElement]) < 0) {
            pair<int, char> i = (*string)[firstElement];
            (*string)[firstElement] = (*string)[lastElement];
            (*string)[lastElement] = i;
        }
    } else {

        int middleIter = (firstElement + (lastElement - firstElement) / 2) + 1;

        sortString(string, firstElement, middleIter - 1);
        sortString(string, middleIter, lastElement);

        int firstIter = firstElement;

        int secondIter = middleIter;

        vector<pair<int, char>> middleInts(lastElement - firstElement + 1);

        for (int i = 0; i <= lastElement - firstElement; ++i) {
            if (compare((*string)[firstIter], (*string)[secondIter]) >= 1) {
                middleInts[i] = (*string)[firstIter++];
                if (firstIter == middleIter) {
                    for (int j = i + 1; j <= lastElement - firstElement; ++j) {
                        middleInts[j] = (*string)[secondIter++];
                    }
                    break;
                }
            } else {
                middleInts[i] = (*string)[secondIter++];
                if (secondIter == lastElement + 1) {
                    for (int j = i + 1; j <= lastElement - firstElement; ++j) {
                        middleInts[j] = (*string)[firstIter++];
                    }
                    break;
                }
            }
        }

        for (int i = 0; i <= lastElement - firstElement; ++i) {
            (*string)[firstElement + i] = middleInts[i];
        }
    }
}

int main() {

    int numberOfString;
    cin >> numberOfString;

    string lastColumn;
    cin >> lastColumn;

    vector<pair<int, char>> firstColumn(lastColumn.size());

    for (int i = 0; i < lastColumn.size(); ++i) {
        firstColumn.at(i).first = i;
        firstColumn.at(i).second = lastColumn[i];
    }

    sortString(&firstColumn, 0, firstColumn.size() - 1);

    int num = numberOfString-1;

    for (int i = 0; i < lastColumn.size(); i++) {
        cout << firstColumn[num].second;
        num = firstColumn[num].first;
    }

    cout << endl;

    return 0;
}