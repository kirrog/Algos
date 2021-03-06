#include <cstring>
#include <iostream>

using namespace std;

#define MAX 1010

int graph[MAX][MAX], g[MAX][MAX];

int used[MAX];
int n;

void dfs(int v, int type) {
    used[v] = 1;
    for (int i = 0; i < n; i++) {
        if ((type ? g[i][v] : g[v][i]) && !used[i]) dfs(i, type);
    }
}

int AllVisited() {
    for (int i = 0; i < n; i++)
        if (!used[i]) return 0;
    return 1;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }
    int L = 0;
    int R = 2000000000;
    while (L < R) {
        int Mid = (L + R) / 2;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                g[i][j] = (graph[i][j] <= Mid);
        memset(used, 0, sizeof(used));
        dfs(0, 0);
        int flag = 0;
        if (AllVisited()) {
            memset(used, 0, sizeof(used));
            dfs(0, 1);
            if (!AllVisited())
                flag = 1;
        } else
            flag = 1;
        if (!flag)
            R = Mid;
        else
            L = Mid + 1;
    }
    cout << L;
    return 0;
}