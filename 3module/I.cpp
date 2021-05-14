
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int cars;
    cin >> cars;
    int floorSize;
    cin >> floorSize;
    int orderNum;
    cin >> orderNum;

    int result = 0;

    if (cars > floorSize) {
        if (orderNum > floorSize) {

            vector<int> floor(floorSize, 0);
            vector<int> allCars(orderNum);
            vector<vector<int>> orderOfCars(cars);
            vector<int> numOfOrder(cars, 0);

            for (int i = 0; i < orderNum; ++i) {
                int car;
                cin >> car;
                allCars[i] = car;
                orderOfCars[car - 1].push_back(i);
            }

            for (int i = 0; i < orderNum; ++i) {
                int car = allCars[i];

                int farrest = -1;
                int farrestPos = -1;
                bool found = false;
                for (int j = 0; j < floorSize; ++j) {
                    if (floor[j] == 0) {
                        floor[j] = car;
                        numOfOrder[floor[j] - 1]++;
                        found = true;
                        result++;
                        break;
                    } else {
                        if (floor[j] == car) {
                            found = true;
                            numOfOrder[floor[j] - 1]++;
                            break;
                        }
                        if (numOfOrder[floor[j] - 1] != orderOfCars[floor[j] - 1].size() && farrestPos < orderOfCars[floor[j] - 1][numOfOrder[floor[j] - 1]]) {
                            farrestPos = orderOfCars[floor[j] - 1][numOfOrder[floor[j] - 1]];
                            farrest = j;
                        } else if(numOfOrder[floor[j] - 1] == orderOfCars[floor[j] - 1].size()){
                            farrestPos = orderNum;
                            farrest = j;
                        }
                    }
                }
                if (!found) {
                    floor[farrest] = car;
                    numOfOrder[car - 1]++;
                    result++;
                }
            }
        } else {
            result = orderNum;
        }
    } else {
        result = cars;
    }

    printf("%d", result);

    return 0;
}
