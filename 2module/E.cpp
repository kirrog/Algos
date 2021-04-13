#include <iostream>
#include <vector>

bool checkPositions(int minimalDistance, std::vector<int> *positions, int cows) {
    int prevPos = positions->at(0);
    int cowNumber = 1;
    for (int i = 1; i < positions->size(); ++i) {
        if (positions->at(i) - prevPos >= minimalDistance) {
            cowNumber++;
            prevPos = positions->at(i);
            if (cowNumber == cows) {
                return true;
            }
        }
    }
    return false;
}


int main() {
    int pos;
    std::cin >> pos;
    int cow;
    std::cin >> cow;
    std::vector<int> positions(pos);
    for (int i = 0; i < (int) pos; ++i) {
        std::cin >> positions[i];
    }

    int leftBorder = 1;
    int rightBorder = positions[positions.size() - 1];

    while (rightBorder - leftBorder != 1) {
        int center = (rightBorder + leftBorder) / 2;
        if(checkPositions(center, &positions, cow)){
           leftBorder = center;
        } else{
            rightBorder = center;
        }
    }

    printf("%d", leftBorder);

    return 0;
}