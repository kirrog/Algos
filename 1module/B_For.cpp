
#include <iostream>
#include <deque>
#include <vector>

struct thing {
    int num;
    char charOfThing;
};

int main() {

    std::deque<struct thing> things;

    int numOfAnimals = 0;
    int numOfTraps = 0;

    char nextChar;
    while ((nextChar = std::cin.get()) != EOF) {
        struct thing th;
        th.charOfThing = nextChar;
        if (nextChar > 96) {
            th.num = ++numOfAnimals;
        } else if (nextChar < 91) {
            th.num = ++numOfTraps;
        }
        things.push_back(th);
    }

    std::vector<int> order(things.size() / 2, 0);
    int size = things.size();

    int pushedRound = 0;
    bool happenedSlop = false;

    for (int i = 0; i < size; ++i) {
        struct thing currentThing;

        if (happenedSlop && pushedRound > 0) {
            currentThing = things.back();
            things.pop_back();
            pushedRound--;
        } else {
            currentThing = things.front();
            things.pop_front();
        }

        if (things.empty()) {
            printf("Impossible");
            return 0;
        }

        int next = (int) currentThing.charOfThing - (int) things.front().charOfThing;
        int prev = (int) currentThing.charOfThing - (int) things.back().charOfThing;

        if (next == 32) {//Next trap
            order[things.front().num - 1] = currentThing.num;
            things.pop_front();
            happenedSlop = true;
        } else if (prev == 32) {//Prev trap
            order[things.back().num - 1] = currentThing.num;
            things.pop_back();
            if(pushedRound > 0 && !happenedSlop){
                pushedRound--;
            }
            happenedSlop = true;
        } else if (next == -32) {//Next animal
            order[currentThing.num - 1] = things.front().num;
            things.pop_front();
            happenedSlop = true;
        } else if (prev == -32) {//Prev animal
            order[currentThing.num - 1] = things.back().num;
            things.pop_back();
            if(pushedRound > 0 && !happenedSlop){
                pushedRound--;
            }
            happenedSlop = true;
        } else {
            happenedSlop = false;
            things.push_back(currentThing);
            pushedRound++;
        }
        if (things.empty()) {
            break;
        }
        for (int j = 0; j < things.size(); ++j) {
            printf("%d.%c ", things[j].num, things[j].charOfThing);
        }
        printf("\n");
    }

    if (things.empty()) {
        printf("Possible\n");
        for (int ord : order) {
            printf("%d ", ord);
        }
    } else {
        printf("Impossible");
    }

    return 0;
}