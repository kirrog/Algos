
#include <vector>
#include <iostream>

using namespace std;

int find_min(vector<int> &data, int tree_l_bord, int tree_r_bord) {
    if (tree_l_bord == tree_r_bord) {
        return data[tree_l_bord];
    } else if (tree_r_bord - tree_l_bord == 1) {
        return min(data[tree_l_bord], data[tree_r_bord]);
    } else {
        int mid = (tree_l_bord + tree_r_bord) / 2;
        int l = find_min(data, tree_l_bord, mid);
        int r = find_min(data, mid + 1, tree_r_bord);
        return min(l, r);
    }
}

void update_tree(vector<int> &tree, vector<int> &links, int pos, int val, int tree_l_bord, int tree_r_bord) {
    if (links[pos] == -1) {
        links[pos] = pos + 1;
    }
    int p = links[pos];
    tree[p] = val;
    while (p > 1 && tree[p] < tree[p / 2]) {
        swap(tree[p], tree[p / 2]);
        int sec_pos = -1;
        for (int i = 0; i < links.size(); ++i) {
            if (links[i] == p / 2) {
                sec_pos = i;
            }
        }
        swap(links[pos], links[sec_pos]);
        p = p / 2;
    }
    while (((p * 2 < tree.size() && tree[p] > tree[p * 2]) || (p * 2 + 1 < tree.size() && tree[p] > tree[p * 2 + 1]))) {
        if ((p * 2 < tree.size() && tree[p] > tree[p * 2]) && tree[p * 2] < tree[p * 2 + 1]) {
            swap(tree[p], tree[p * 2]);
            int sec_pos = -1;
            for (int i = 0; i < links.size(); ++i) {
                if (links[i] == p * 2) {
                    sec_pos = i;
                }
            }
            swap(links[pos], links[sec_pos]);
            p = p * 2;
        } else if ((p * 2 + 1 < tree.size() && tree[p] > tree[p * 2 + 1]) && tree[p * 2] >= tree[p * 2 + 1]) {
            swap(tree[p], tree[p * 2 + 1]);
            int sec_pos = -1;
            for (int i = 0; i < links.size(); ++i) {
                if (links[i] == p * 2 + 1) {
                    sec_pos = i;
                }
            }
            swap(links[pos], links[sec_pos]);
            p = p * 2 + 1;
        }
    }
}

int main() {
    int order;
    int size;
    cin >> order;
    cin >> size;

    vector<int> links(size, -1);
    vector<int> tree(size + 1, INT32_MAX);

    for (int i = 0; i < order; ++i) {
        int elem;
        cin >> elem;
        update_tree(tree, links, i % size, elem, 0, size - 1);
        if (i >= size - 1) {
            int res = tree[1];
            printf("%d ", res);
        }
    }

    return 0;
}