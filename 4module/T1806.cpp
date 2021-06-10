#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>

using namespace std;

struct Solder {
    Solder *prev;
    int num;
    bool front = false;
    int time = 0;
    bool checked = false;
    vector<char> number;
};

int communicateCost(Solder a, Solder b) {
    int zeros = 0;
    int fir = -1;
    int sec = -1;
    for (int i = 0; i < 10; ++i) {
        if (a.number[i] == b.number[i]) {
            zeros++;
        } else {
            if (fir == -1) {
                fir = i;
            } else {
                sec = i;
            }
        }
    }
    if (zeros == 9) {
        return fir;
    } else if (zeros == 8) {
        if (a.number[fir] == b.number[sec] && a.number[sec] == b.number[fir]) {
            return fir;
        }
    }
    return -1;
}

int comparator(Solder *a, Solder *b) {
    return a->time > b->time;
}

bool addElem(vector<Solder *> &heap, int dist, Solder *solder, Solder *prev) {
    if (!solder->checked) {
        if (!solder->front) {
            solder->front = true;
            solder->prev = prev;
            solder->time = prev->time + dist;
            heap.push_back(solder);
            push_heap(heap.begin(), heap.end(), comparator);
            return true;
        } else {
            if (solder->time > (prev->time + dist)) {
                solder->time = prev->time + dist;
                solder->prev = prev;
                make_heap(heap.begin(), heap.end(), comparator);
            }
            return false;
        }
    } else {
        return false;
    }
}

bool finding(vector<vector<int>> &differs, vector<Solder> &solders) {
    vector<Solder *> front;
    front.reserve(solders.size());
    front.push_back(&solders[0]);
    solders[0].front = true;
    int frontSize = 1;
    while (!solders[solders.size() - 1].checked && frontSize) {
        auto iter = front.begin();
        Solder *solder = (*iter);

        pop_heap(front.begin(), front.end(), comparator);
        front.pop_back();
        frontSize--;

        solder->checked = true;

        for (int i = 0; i < solders.size(); ++i) {
            int dist = differs[solder->num][i];
            if (dist >= 0) {
                if (addElem(front, dist, &(solders[i]), solder)) frontSize++;
            }
        }
    }
    return (solders[solders.size() - 1].checked);
}

int main() {

    int soldersSize;
    cin >> soldersSize;
    vector<Solder> solders(soldersSize);
    vector<int> times(10);
    for (int i = 0; i < 10; ++i) {
        cin >> times[i];
    }

    for (int i = 0; i < soldersSize; ++i) {
        char array[10];
        cin >> array;
        solders[i].number.resize(10);
        solders[i].num = i;
        for (int j = 0; j < 10; ++j) {
            solders[i].number[j] = ((int) array[j]) - 48;
        }
    }

    vector<vector<int>> differs(soldersSize);
    for (int i = 0; i < soldersSize; ++i) {
        differs[i].resize(soldersSize, -1);
    }
    for (int i = 0; i < soldersSize; ++i) {
        for (int j = i + 1; j < soldersSize; ++j) {
            if (differs[i][j] == -1) {
                int diff = communicateCost(solders[i], solders[j]);
                if (diff > -1) {
                    differs[i][j] = times[diff];
                    differs[j][i] = times[diff];
                }
            }
        }
    }


    if (finding(differs, solders)) {
        deque<int> order;
        int resultSize = 0;

        Solder *iter = &solders[soldersSize - 1];
        while (iter) {
            order.push_front(iter->num);
            resultSize++;
            iter = iter->prev;
        }


        cout << (solders[soldersSize - 1].time) << endl;
        cout << resultSize << endl;//
        for (auto item:order) {
            cout << (item + 1) << " ";
        }
        cout << endl;
    } else {
        cout << -1 << endl;
    }


    return 0;
}