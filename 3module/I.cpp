
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

typedef int car;
typedef int pos;

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

            vector<int> allCars(orderNum);
            vector<vector<int>> orderOfCars(cars);
            vector<int> iterOfOrder(cars, 0);

            for (int i = 0; i < orderNum; ++i) {
                int carNum;
                cin >> carNum;
                allCars[i] = carNum;
                orderOfCars[carNum - 1].push_back(i);
            }

            map<pos, car, greater<pos>> floorCarsOrdered; // first - pos, second - car
            unordered_map<car, pos> floorCars;

            int diff = 0;

            for (int i = 0; i < orderNum; ++i) {
                car carNum = allCars[i];

                auto changeableCar = floorCars.find(carNum);

                if (changeableCar == floorCars.end()) {// didn't find this carNum
                    result++;
//                    for (int j = 0; j < iterOfOrder.size(); ++j) {
//                        printf("%d ", iterOfOrder[j]);
//                    }
//                    printf("\n");
                    if (floorCarsOrdered.size() == floorSize) {// floor is full
                        auto pairDel = floorCarsOrdered.begin();
                        pos p = pairDel->first;
                        car c = pairDel->second;
                        floorCarsOrdered.erase(p);
                        floorCars.erase(c);
                    }
                } else {
                    floorCarsOrdered.erase(changeableCar->second);
                }

                int index = ++iterOfOrder[carNum - 1];
                pos posNextCar;

                if (index >= orderOfCars[carNum - 1].size()) {
                    posNextCar = (orderNum + (diff++));// pos higher than any other
                } else {
                    posNextCar = orderOfCars[carNum - 1][index];
                }
                // adding next car at floor
                floorCarsOrdered[posNextCar] = carNum;
                floorCars[carNum] = posNextCar;


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
