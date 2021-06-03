#include <cstring>
#include <fstream>

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
    std::ifstream file("avia.in");
    std::string s;
    getline(file, s);
    n = std::atoi(s.c_str());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> graph[i][j];
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
    std::ofstream file1("avia.out");
    file1 << L;
    return 0;
}