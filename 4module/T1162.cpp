#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int A;
    int B;
    double rAB;
    double cAB;
};

int main() {

    int currencies, pointsSize, type;
    double value;
    cin >> currencies >> pointsSize >> type >> value;
    vector<double> availableResults(currencies, 0);
    availableResults[--type] = value;
    vector<Point> points(pointsSize * 2);
    for (int i = 0; i < pointsSize; ++i) {
        int a, b;
        double rab, cab, rba, cba;
        cin >> a >> b;
        a--;
        b--;
        cin >> rab >> cab >> rba >> cba;
        points[i * 2].A = a;
        points[i * 2].B = b;
        points[i * 2].rAB = rab;
        points[i * 2].cAB = cab;
        points[i * 2 + 1].A = b;
        points[i * 2 + 1].B = a;
        points[i * 2 + 1].rAB = rba;
        points[i * 2 + 1].cAB = cba;
    }

    bool check = false;

    for (int i = 0; i < currencies - 1; ++i) {
        for (int j = 0; j < pointsSize * 2; ++j) {
            if (availableResults[points[j].A]) {
                double result = availableResults[points[j].A] - points[j].cAB;
                availableResults[points[j].B] = max(availableResults[points[j].B], result * points[j].rAB);
            }
        }
    }
    for (int i = 0; !check && (i < pointsSize * 2); ++i) {
        double result = availableResults[points[i].A] - points[i].cAB;
        if (result * points[i].rAB > availableResults[points[i].B]) {
            check = true;
        }
    }

    if (check) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}