#include <iostream>

using namespace std;

struct Point {
    int firCur;
    int secCur;
    double rAB;
    double cAB;
    double rBA;
    double cBA;
};

struct PointCheck {
    bool checked = false;
};

int main() {

    int currencies, points, type, value;
    cin >> currencies >> points >> type >> value;

    vector <Point> points(points);
    vector <PointCheck> pointsChecks(points);
    for (int i = 0; i < points; ++i) {
        cin >> points[i];
    }

    bool check = false;

    //bsf - в ширину поиск с учётом циклов. Получим выгодные пути. При наличии идём по ним

    if (check) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}