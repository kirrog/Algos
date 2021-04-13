//2module/E.cpp

#include <vector>
#include <deque>

using namespace std;

int main() {
    deque<int> goblins;
    auto iter = goblins.begin();
    goblins.push_back(0);
    goblins.push_back(1);
    goblins.push_back(2);
    goblins.push_back(3);
    goblins.push_back(4);

    iter++;
    iter++;
    iter++;

    goblins.insert(iter, 5);

    return 0;
}