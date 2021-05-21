#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;




int main() {

    long long int cars, floor, order, i, n, T = 0, result = 0;
    cin >> cars >> floor >> order; //if (K>100) { cout<<order-4; return 0;};

    vector<long long int> carOrder(order + 1);

    vector<long long int> carNumber(cars);//номер машинки

    vector<long long int> nextCarNumber(100002);//в какой следующий момент будет нужна на полу(по этому значению строится максимальная куча)
    //индекс sost - номер машинки
    vector<bool> inHeap(100002, 0); //есть ли в куче(на полу)

    vector<vector<long long int> > nextOnFloor(100002); // в какие моменты нужна на полу

    vector<long long int> idInHeap(100002); // индекс в куче
    for (i = 1; i <= cars; i++) {
        nextOnFloor[i].push_back(order + 1);
    }
    for (i = 1; i <= order; i++) {
        cin >> n;
        carOrder[i] = n;
    }
    for (i = order; i >= 1; i--) {
        nextOnFloor[carOrder[i]].push_back(i);
    }
    for (i = 1; i <= cars; i++) {
        nextOnFloor[i].pop_back();
    }
    i = 0;

    while (T != floor) {
        i++;
        if (inHeap[carOrder[i]] == 0) {
            T++;
            result++;
            carNumber[T] = carOrder[i];
            nextCarNumber[T] = nextOnFloor[carOrder[i]].back();
            nextOnFloor[carOrder[i]].pop_back();
            idInHeap[carOrder[i]] = T;
            inHeap[carOrder[i]] = 1;
            int index = T;
            while (index / 2 != 0 && nextCarNumber[index] > nextCarNumber[index / 2]) {
                idInHeap[carNumber[index]] = index / 2;
                idInHeap[carNumber[index / 2]] = index;
                swap(carNumber[index], carNumber[index / 2]);
                swap(nextCarNumber[index], nextCarNumber[index / 2]);
                index = index / 2;
            }
        } else {
            nextCarNumber[idInHeap[carOrder[i]]] = nextOnFloor[carOrder[i]].back();
            nextOnFloor[carOrder[i]].pop_back();
            int index = idInHeap[carOrder[i]];
            while (index / 2 != 0 && nextCarNumber[index] > nextCarNumber[index / 2]) {
                idInHeap[carNumber[index]] = index / 2;
                idInHeap[carNumber[index / 2]] = index;
                swap(carNumber[index], carNumber[index / 2]);
                swap(nextCarNumber[index], nextCarNumber[index / 2]);
                index = index / 2;
            }
        }
        if (i == order) {
            cout << result;
            return 0;
        }
    }

    while (i < order) {
        i++;
        if (inHeap[carOrder[i]] == 1) {
            nextCarNumber[idInHeap[carOrder[i]]] = nextOnFloor[carOrder[i]].back();
            nextOnFloor[carOrder[i]].pop_back();
            int index = idInHeap[carOrder[i]];
            while (index / 2 != 0 && nextCarNumber[index] > nextCarNumber[index / 2]) {
                idInHeap[carNumber[index]] = index / 2;
                idInHeap[carNumber[index / 2]] = index;
                swap(carNumber[index], carNumber[index / 2]);
                swap(nextCarNumber[index], nextCarNumber[index / 2]);
                index = index / 2;
            }
        } else {
            result++;
            inHeap[carNumber[1]] = 0;
            carNumber[1] = carOrder[i];
            nextCarNumber[1] = nextOnFloor[carOrder[i]].back();
            inHeap[carOrder[i]] = 1;
            nextOnFloor[carOrder[i]].pop_back();
            idInHeap[carOrder[i]] = 1;

            int index = 1;

            if (2 * index > floor) {
            } else if (2 * index == floor) {
                if (nextCarNumber[2 * index] <= nextCarNumber[index]) {

                }else{
                    idInHeap[carNumber[index]] = 2 * index;
                    idInHeap[carNumber[2 * index]] = index;
                    swap(carNumber[index], carNumber[2 * index]);
                    swap(nextCarNumber[index], nextCarNumber[2 * index]);
                }
            }else {
                if (nextCarNumber[index] < max(nextCarNumber[2 * index], nextCarNumber[2 * index + 1])) {
                    long long int t;
                    if (nextCarNumber[2 * index] > nextCarNumber[2 * index + 1]) t = 2 * index;
                    else t = 2 * index + 1;
                    idInHeap[carNumber[index]] = t;
                    idInHeap[carNumber[t]] = index;
                    swap(carNumber[index], carNumber[t]);
                    swap(nextCarNumber[index], nextCarNumber[t]);
                }
            }
        };
    };
    cout << result;
    return 0;
}
