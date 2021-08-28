#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <deque>
#include <string>
#include <algorithm>

using namespace std;

long long powNum[] = {1000000000l, 100000000l, 10000000l, 1000000l, 100000l, 10000l, 1000l, 100l, 10l, 1l};

struct Solder {
    Solder *prev;
    int num;
    int time = 0;
    bool front = false;
    bool checked = false;
    long long number;
    unordered_map<Solder *, int> neighbors;
};

long long changePos(long long numOld, int firPos, int secPos) {
    int fir = (numOld / (powNum[firPos])) % 10;
    int sec = (numOld / (powNum[secPos])) % 10;
    long long num = numOld;
    num -= fir * powNum[firPos];
    num -= sec * powNum[secPos];
    num += fir * powNum[secPos];
    num += sec * powNum[firPos];
    return num;
}

long long changeNum(long long num, int pos, int n) {
    int fir = (num / (powNum[pos])) % 10;
    num -= fir * powNum[pos];
    num += n * powNum[pos];
    return num;
}


void findNeighbours(Solder *solder, unordered_map<long long int, Solder> &map, vector<int> &times) {
    long long number = solder->number;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            long long res = changeNum(number, i, j);
            if (res != number) {
                auto item = map.find(res);
                if (item != map.end()) {
//                    cout << number << " - " << res << endl;
                    solder->neighbors.insert(make_pair(&(item->second), times[i]));
//                    item->second.neighbors.insert(make_pair(solder, times[i]));
                }
            }
        }
        for (int j = i + 1; j < 10; ++j) {
            long long res = changePos(number, i, j);
            if (res != number) {
                auto item = map.find(res);
                if (item != map.end()) {
//                    cout << number << " - " << res << endl;
                    solder->neighbors.insert(make_pair(&(item->second), times[i]));
//                    item->second.neighbors.insert(make_pair(solder, times[i]));
                }
            }
        }
    }
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

bool finding(Solder *start, Solder *end, int size) {
    vector<Solder *> front;
    front.reserve(size);
    front.push_back(start);
    start->front = true;
    int frontSize = 1;
    while (!end->checked && frontSize) {
        auto iter = front.begin();
        Solder *solder = (*iter);

        pop_heap(front.begin(), front.end(), comparator);
        front.pop_back();
        frontSize--;

        solder->checked = true;

        for (auto neighbor:solder->neighbors) {
            int dist = neighbor.second;
            if (addElem(front, dist, neighbor.first, solder)) frontSize++;
        }
    }
    return (end->checked);
}

int main() {

    int soldersSize;
    cin >> soldersSize;
//    vector<Solder> solders(soldersSize);
    vector<int> times(10);
    unordered_map<long long, Solder> mapOfSolders(soldersSize);
    for (int i = 0; i < 10; ++i) {
        cin >> times[i];
    }

    Solder *start = nullptr;
    Solder *end = nullptr;
    for (int i = 0; i < soldersSize; ++i) {
        Solder sold;
        sold.num = i;
        string str;
        long long init;
        cin >> str;
        init = stoll(str);
        sold.number = init;
        pair<long long, Solder> in = make_pair(init, sold);
        auto iter = mapOfSolders.insert(in);
        if (i == 0) {
            start = &(iter.first->second);
        }
        if (i == soldersSize - 1) {
            end = &(iter.first->second);
        }
    }

    for (auto item: mapOfSolders) {
        findNeighbours(&(item.second), mapOfSolders, times);
    }

    if (finding(start, end, soldersSize)) {
        vector<int> order(soldersSize);
        int resultSize = 0;

        Solder *iter = end;
        while (iter) {
            order[resultSize++] = (iter->num);
            iter = iter->prev;
        }

        cout << (end->time) << endl;
        cout << resultSize << endl;
        for (int i = resultSize - 1; i >= 0; i--) {
            cout << (order[i] + 1) << " ";
        }
        cout << endl;
    } else {
        cout << -1 << endl;
    }


    return 0;
}