#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> BlackPoint;

bool horizontalComparator(BlackPoint a, BlackPoint b) {
    if (a.first != b.first) return a.first < b.first;
    return a.second < b.second;
}

bool verticalComparator(BlackPoint a, BlackPoint b) {
    if (a.second != b.second) return a.second < b.second;
    return a.first < b.first;
}


int main() {
    long width, height, pointsNum, ans = 0;

    cin >> width >> height >> pointsNum;

    vector<BlackPoint> cell((width * 2) + (height * 2) + pointsNum);
    set<BlackPoint> alonePoints;

    for (long i = 0, x, y; i < pointsNum; ++i) {
        cin >> x >> y;
        cell[i] = make_pair(x, y);
    }

    for (long i = 1; i <= height; i++) {
        cell[pointsNum++] = make_pair(0, i);
        cell[pointsNum++] = make_pair(width + 1, i);
    }

    for (long i = 1; i <= width; i++) {
        cell[pointsNum++] = make_pair(i, 0);
        cell[pointsNum++] = make_pair(i, height + 1);
    }

    sort(cell.begin(), cell.begin() + pointsNum, horizontalComparator);
    for (int i = 0; i + 1 < pointsNum; i++) {
        int diff = cell[i + 1].second - cell[i].second;
        if (cell[i].first == cell[i + 1].first && diff >= 2) {
            if (diff == 2) {
                alonePoints.insert(make_pair(cell[i].first, cell[i].second + 1));
            } else {
                ++ans;
            }
        }
    }

    sort(cell.begin(), cell.begin() + pointsNum, verticalComparator);
    for (int i = 0; i + 1 < pointsNum; ++i) {
        int diff = cell[i + 1].first - cell[i].first;
        if (cell[i].second == cell[i + 1].second && diff >= 2) {
            if (diff == 2) {
                if (alonePoints.find(make_pair(cell[i].first + 1, cell[i].second)) != alonePoints.end()) {
                    ++ans;
                }
            } else {
                ++ans;
            }
        }
    }

    cout << ans << endl;

    return 0;
}