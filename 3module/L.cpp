
#include <vector>
#include <iostream>
#include <limits>

using namespace std;

void build_min_tree(vector<int> &data, vector<int> &tree, int val, int tree_left_border, int tree_right_border) {
    if (tree_left_border == tree_right_border) {
        tree[val] = data[tree_left_border];
    } else {
        int tree_mid = (tree_left_border + tree_right_border) / 2;
        build_min_tree(data, tree, val * 2, tree_left_border, tree_mid);
        build_min_tree(data, tree, val * 2 + 1, tree_mid + 1, tree_right_border);
        tree[val] = min(tree[val * 2], tree[val * 2 + 1]);
    }
}

int find_min(vector<int> &tree, int v_p, int l_b, int r_b, int t_l_b, int t_r_b) {
    if (t_r_b < l_b || t_l_b > r_b) {
        return std::numeric_limits<int>::max();
    } else if (t_l_b >= l_b && t_r_b <= r_b) {
        return tree[v_p];
    } else {
        int t_m = (t_l_b + t_r_b) / 2;
        int l = find_min(tree, v_p * 2, l_b, min(r_b, t_m), t_l_b, t_m);
        int r = find_min(tree, v_p * 2 + 1, max(l_b, t_m + 1), r_b, t_m + 1, t_r_b);
        return min(l, r);
    }
}

int main() {
    int order;
    int size;
    cin >> order;
    cin >> size;

    vector<int> data(order);
    vector<int> tree(order * 3);

    for (int i = 0; i < order; ++i) {
        cin >> data[i];
    }

    build_min_tree(data, tree, 1, 0, order - 1);

    for (int i = 0, j = size - 1; j < order; ++i, j++) {
        int res = find_min(tree, 1, i, j, 0, order - 1);
        cout << res << " ";
    }

    cout << std::endl;

    return 0;
}