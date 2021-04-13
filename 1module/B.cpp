
#include <iostream>
#include <stack>
#include <vector>


int main() {
    std::string strIn;
    std::cin >> strIn;
    std::deque<std::pair<int, char>> zoo;

    int numOfAnimals = 0;
    int numOfTraps = 0;

    for (int i = 0; i < strIn.size(); ++i) {
        std::pair<int, char> pair;
        pair.second = strIn[i];
        if (pair.second > 96) {
            pair.first = ++numOfAnimals;
        } else if (pair.second < 91) {
            pair.first = ++numOfTraps;
        }
        zoo.push_back(pair);
    }

    std::vector<int> order(zoo.size() / 2, 0);

    int size = zoo.size();
    int shift = 0;
    for (int i = 0; i < size; ++i) {
        std::pair<int, char> currentPair = zoo.front();
        zoo.pop_front();
        int compare = ((int) currentPair.second) - ((int) zoo.front().second);
        if (compare == 32) {//next trap
            order[zoo.front().first - 1] = currentPair.first;
            zoo.pop_front();
            if (shift > 0 && !zoo.empty()) {
                currentPair = zoo.back();
                zoo.pop_back();
                zoo.push_front(currentPair);
                shift--;
            }

        } else if (compare == -32) {//next anim
            order[currentPair.first - 1] = zoo.front().first;
            zoo.pop_front();
            if (shift > 0 && !zoo.empty()) {
                currentPair = zoo.back();
                zoo.pop_back();
                zoo.push_front(currentPair);
                shift--;
            }
        } else if (shift == 0) {
            int comparePrev = ((int) currentPair.second) - ((int) zoo.back().second);
            if (comparePrev == 32) {//prev trap
                order[zoo.back().first - 1] = currentPair.first;
                zoo.pop_back();
            } else if (comparePrev == -32) {//prev anim
                order[currentPair.first - 1] = zoo.back().first;
                zoo.pop_back();
            }else {
                zoo.push_back(currentPair);
                shift++;
                if (shift >= zoo.size()) {
                    printf("Impossible");
                    return 0;
                }
            }
        } else {
            zoo.push_back(currentPair);
            shift++;
            if (shift >= zoo.size()) {
                printf("Impossible");
                return 0;
            }
        }
        if (zoo.empty()) {
            break;
        }
    }

    printf("Possible\n");
    for (int ord : order) {
        printf("%d ", ord);
    }

    return 0;
}