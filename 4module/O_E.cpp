#include <iostream>
#include <vector>

using namespace std;


int color = 2, fl = 0, ogo = 0, todo = 0;
vector<int> count(200), color2(200), min2(200);
vector<vector<int>> arr(200), adj(200), used(200);

void dfs(int d, int pred, int od) {
    if (color2[d] != 0) {
        if (color2[d] == color2[od] && d != od) {
            ogo = 1;
        }
        return;
    }
    if (used[pred][d])
        return;
    if (d == pred)
        color2[d] = 1;
    else {
        if (color2[od] == 1) {
            color2[d] = 2;
        } else if (color2[od] != 0)
            color2[d] = 1;
        else
            color2[d] = 1;
    }
    used[pred][d] = true;
    min2[pred]++;
    todo = 0;

    for (int i = 0; i < count[d]; i++) {
        dfs(adj[d][i], pred, d);
    }
    todo = 1;
}

int main() {
    int n, m, coun = 0;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        arr[i].resize(200);
        adj[i].resize(200);
        used[i].resize(200);
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        arr[a][b] = 1;
        arr[b][a] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j] == 1) {
                adj[i][count[i]] = j;
                count[i]++;
                coun++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        dfs(i, i, i);
    }

    if (!ogo)
        cout << "YES";
    else
        cout << "NO";
}
