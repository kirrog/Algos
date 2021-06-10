#include <cstdio>
#include <vector>
#include <climits>
#include <algorithm>
#include <deque>

using namespace std;

struct Node {
    int i;
    int j;
    int dist; // расстояние от стартовой точки
    int weight;
    bool visited;
    char from;
};

bool operator== (const Node &left, const Node &right) {
    return (right.i == left.i && right.j == left.j);
}

bool operator!= (const Node &left, const Node &right) {
    return (right.i != left.i || right.j != left.j);
}

bool operator>(const Node &left, const Node &right) {
    return left.dist > right.dist;
}

const int INF = 1001;
int n;
int m;
Node start;
Node finish;

int main() {
    scanf("%d %d %d %d %d %d",
          &n, &m, &start.i, &start.j, &finish.i, &finish.j);
    start.i--;
    start.j--;
    finish.i--;
    finish.j--;

    vector< vector<Node> > a(n, vector<Node>(m));

    char type;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf(" %c", &type);
            if (type == '.') a[i][j].weight = 1;
            else if (type == 'W') a[i][j].weight = 2;
            else if (type == '#') a[i][j].weight = INF;
            a[i][j].i = i;
            a[i][j].j = j;
            a[i][j].from = '#';
            a[i][j].visited = false;
            if (a[i][j] == start) {
                a[i][j].dist = 0;
            } else {
                a[i][j].dist = INF;
            }
        }
    }

    // дейкстра для поиска путей до всех точек
    vector<Node*> front; // хранит дистанции от старта до всех точек
    front.reserve(n * m);
    front.push_back(&a[start.i][start.j]);
//    make_heap(front.begin(), front.end(), greater<>{});
    Node * current;
    while (!front.empty()) {
        Node * v = front[0];
        pop_heap(front.begin(), front.end());
        front.pop_back();
        int dist = v->dist;
        // берем верхнуюю
        if (v->i > 0) {
            current = &a[v->i - 1][v->j];
            if (!current->visited && dist + current->weight < current->dist) {
                current->dist = dist + current->weight;
                current->from = 'N';
                front.push_back(current);
                push_heap(front.begin(), front.end());
            }
        }
        // берем нижнюю
        if (v->i < n - 1) {
            current = &a[v->i + 1][v->j];
            if (!current->visited && dist + current->weight < current->dist) {
                current->dist = dist + current->weight;
                current->from = 'S';
                front.push_back(current);
                push_heap(front.begin(), front.end());
            }
        }
        // берем левую
        if (v->j > 0) {
            current = &a[v->i][v->j - 1];
            if (!current->visited && dist + current->weight < current->dist) {
                current->dist = dist + current->weight;
                current->from = 'W';
                front.push_back(current);
                push_heap(front.begin(), front.end());
            }
        }
        // берем правую
        if (v->j < m - 1) {
            current = &a[v->i][v->j + 1];
            if (!current->visited && dist + current->weight < current->dist) {
                current->dist = dist + current->weight;
                current->from = 'E';
                front.push_back(current);
                push_heap(front.begin(), front.end());

            }
        }
//        make_heap(front.begin(), front.end(), less<>{});
    }

    /*
    // вывод расстояний до каждой точки
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j].dist < 1000)
                printf("%4d", a[i][j].dist);
            else
                printf(" inf");
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%c ", a[i][j].from);
        }
        printf("\n");
    }
    printf("\n");
    */

    deque<char> ans;
    char symbol;
    int i = finish.i;
    int j = finish.j;
    while (i != start.i || j != start.j) {
        symbol = a[i][j].from;
        if (symbol == 'S') i--;
        if (symbol == 'N') i++;
        if (symbol == 'E') j--;
        if (symbol == 'W') j++;
        ans.push_front(symbol);
    }

    printf("%d\n", a[finish.i][finish.j].dist);
    for (auto i: ans) {
        printf("%c", i);
    }



    return 0;
}
