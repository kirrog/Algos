
#include <iostream>
#include <vector>


//65-90 and 97-122 -> +32

int main() {
    std::string strIn;
    std::cin >> strIn;
    std::vector<std::pair<int, char>> things(strIn.size());
    int numOfAnimals = 0;
    int numOfTraps = 0;

    for (int i = 0; i < strIn.size(); ++i) {
        std::pair<int, char> th;
        th.second = strIn[i];
        if (strIn[i] > 96) {
            th.first = ++numOfAnimals;
            things[i] = th;
        } else if (strIn[i] < 91) {
            th.first = ++numOfTraps;
            things[i] = th;
        } else {
            printf("Wrong entering");
            return -5;
        }
    }

    std::vector<int> order(strIn.size() / 2, 0);
    int currentThing = 0;
    while (!things.empty()) {
        int nextThing = currentThing + 1;
        int prevThing = currentThing - 1;
        if (currentThing == 0) {
            prevThing = things.size() - 1;
        } else if (currentThing == (things.size() - 1)) {
            nextThing = 0;
        }
        int next = (int) things[currentThing].second - (int) things[nextThing].second;
        if (next == 32) {//Next trap
            order[things[nextThing].first - 1] = things[currentThing].first;
            things.erase(things.begin() + currentThing);
            things.erase(things.begin() + currentThing);
            if(currentThing > 0){
                currentThing--;
            }
        } else if (next == -32) {//Next anim
            order[things[currentThing].first - 1] = things[nextThing].first;
            things.erase(things.begin() + currentThing);
            things.erase(things.begin() + currentThing);
            if(currentThing > 0){
                currentThing--;
            }
        } else if(currentThing == 0){
            int prev = (int) things[currentThing].second - (int) things[prevThing].second;
            if (prev == 32) {//Prev trap
                order[things[prevThing].first - 1] = things[currentThing].first;
                things.erase(things.begin() + (things.size() - 1));
                things.erase(things.begin() + currentThing);
                if(currentThing > 0){
                    currentThing--;
                }
            }  else if (prev == -32) {//Prev animal
                order[things[currentThing].first - 1] = things[prevThing].first;
                things.erase(things.begin() + (things.size() - 1));
                things.erase(things.begin() + currentThing);
                if(currentThing > 0){
                    currentThing--;
                }
            } else{
                currentThing++;
                if (currentThing >= things.size()) {
                    printf("Impossible");
                    return 0;
                }
            }
        }else {
            currentThing++;
            if (currentThing >= things.size()) {
                printf("Impossible");
                return 0;
            }
        }
    }
    printf("Possible\n");
    for (int ord : order) {
        printf("%d ", ord);
    }
    return 0;
}