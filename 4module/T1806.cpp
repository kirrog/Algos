#include <iostream>
#include <vector>

using namespace std;

struct solder {
    vector<int> number;
};

int communicateCost(solder a, solder b) {
    // for all numbers calculate and find
    return 0;
}

int main() {

    int soldersSize;
    cin >> soldersSize;
    vector<solder> solders(soldersSize);
    vector<int> times(10);
    for (int i = 0; i < 10; ++i) {
        cin >> times[i];
    }

    for (int i = 0; i < soldersSize; ++i) {
        char array[10];
        cin >> array;
        solders[i].number.reserve(10);
        for (int j = 0; j < 10; ++j) {
            solders[i].number[j] = ((int) array[i]) - 48;
        }
    }

    //creating structure for searching

    return 0;
}