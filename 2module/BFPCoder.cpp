
#include <string>
#include <iostream>
#include <vector>

using namespace std;


int compare(string fir, string sec) {
    if (fir < sec) {
        return 1;
    } else if (fir > sec) {
        return -1;
    } else {
        return 0;
    }
}



void sortString(vector<string> &strings, int firstElement, int lastElement) {

    if (lastElement - firstElement == 0) {
        return;
    } else if (lastElement - firstElement == 1) {
        if (compare((strings)[firstElement], (strings)[lastElement]) < 0) {
            string i = (strings)[firstElement];
            (strings)[firstElement] = (strings)[lastElement];
            (strings)[lastElement] = i;
        }
    } else {

        int middleIter = (firstElement + (lastElement - firstElement) / 2) + 1;

        sortString(strings, firstElement, middleIter - 1);
        sortString(strings, middleIter, lastElement);

        int firstIter = firstElement;

        int secondIter = middleIter;

        vector<string> middleInts(lastElement - firstElement + 1);

        for (int i = 0; i <= lastElement - firstElement; ++i) {
            if (compare((strings)[firstIter], (strings)[secondIter]) >= 1) {
                middleInts[i] = (strings)[firstIter++];
                if (firstIter == middleIter) {
                    for (int j = i + 1; j <= lastElement - firstElement; ++j) {
                        middleInts[j] = (strings)[secondIter++];
                    }
                    break;
                }
            } else {
                middleInts[i] = (strings)[secondIter++];
                if (secondIter == lastElement + 1) {
                    for (int j = i + 1; j <= lastElement - firstElement; ++j) {
                        middleInts[j] = (strings)[firstIter++];
                    }
                    break;
                }
            }
        }

        for (int i = 0; i <= lastElement - firstElement; ++i) {
            (strings)[firstElement + i] = middleInts[i];
        }
    }
}

int main() {
    string basicString;
    cin >> basicString;

    int size = basicString.size();

    vector<string> strings;

    strings.push_back(basicString);

    for (int i = 1; i < size; ++i) {
        string rotatedString(basicString.substr(size - i, size - 1) + basicString.substr(0, size  - i));
        strings.push_back(rotatedString);
    }

    sortString(strings, 0, size-1);

    for (int i = 0; i < size; ++i) {
        if(strings.at(i) == basicString){
            printf("%d\n", i);
            break;
        }
    }

    for (int i = 0; i < size; ++i) {
        printf("%s\n", strings.at(i).c_str());
    }

    return 0;
}