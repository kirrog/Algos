#include <iostream>
#include <limits>

int tree[600000];

void build_tree(int a[], int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = a[tl];
    } else {
        auto tm = (tl + tr) / 2;
        build_tree(a,v * 2, tl, tm);
        build_tree(a,v * 2 + 1, tm + 1, tr);
        tree[v] = std::min(tree[v * 2], tree[v * 2 + 1]);
    }
}

int get_min(int l, int r, int v, int tl, int tr) {
    if (tr < l || r < tl) {
        return std::numeric_limits<int>::max();
    }
    if (l <= tl && tr <= r) {
        return tree[v];
    }
    auto tm = (tl + tr) / 2;
    return std::min(get_min(l, r, v * 2,     tl,     tm), get_min(l, r, v * 2 + 1, tm + 1, tr));
}

int main() {
    int n, k;
    std::cin >> n >> k;
    int arr[n];
    for (int i = 0; i < n;i++){
        std::cin >> arr[i];
    }
    build_tree(arr,1, 0, n - 1);
    auto iter1 = 0;
    auto iter2 = k - 1;
    while (iter2 != n){
        std::cout << get_min(iter1,iter2,1,0,n-1) << " ";
        iter1++;
        iter2++;
    }
    std::cout << std::endl;
    return 0;
}