#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

int main() {

    size_t N, K, P;
    cin >> N >> K >> P;

    vector<size_t> machines;
    vector<vector<size_t>> order_by_machine(N + 1);
    vector<size_t> index(N + 1, 0);
    machines.reserve(P);
    for (int i = 0; i < P; ++i) {
        size_t x;
        cin >> x;
        machines.push_back(x);
        order_by_machine[x].push_back(i);
    }

    size_t res = 0;
    size_t endTime = P;
    map<size_t, size_t, std::greater<std::size_t>> cur_machines_by_time;
    unordered_map<size_t, size_t> cur_machines_with_time;
    for (auto m : machines) {
        auto it = cur_machines_with_time.find(m);
        if (it == cur_machines_with_time.end()) {
            res++;
//            for (int j = 1; j < index.size(); ++j) {
//                printf("%d ", index[j]);
//            }
//            printf("\n");
            if (cur_machines_by_time.size() == K) {
                auto it_to_del = cur_machines_by_time.begin();
                auto machine_to_del = it_to_del->second;
                cur_machines_by_time.erase(it_to_del);
                cur_machines_with_time.erase(machine_to_del);
            }
        } else {
            cur_machines_by_time.erase(it->second);
        }
        auto i = ++index[m];
        auto machine_time = i >= order_by_machine[m].size() ? ++endTime : order_by_machine[m][i];
        cur_machines_by_time[machine_time] = m;
        cur_machines_with_time[m] = machine_time;
//        for(auto cm : cur_machines_with_time)
//            cout << cm.first << ' ';
//        cout << endl;

    }

    cout << res;

    return 0;
}