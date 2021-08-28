#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

struct MemNode {
    size_t start;
    size_t size;
    bool free;
    MemNode *next;
    MemNode *prev;

    size_t position;

    MemNode(size_t start, size_t size, bool free, MemNode *prev, MemNode *next) {
        this->free = free;
        this->start = start;
        this->size = size;
        this->prev = prev;
        if (prev) {
            prev->next = this;
        }
        this->next = next;
        if (next) {
            next->prev = this;
        }
    }

    void remove() {
        this->size = 0;
        if (next) {
            next->prev = prev;
        }
        if (prev) {
            prev->next = next;
        }
    }
};

int compare(MemNode *a, MemNode *b) {
    return a->size > b->size;
}

int parent_heap_pos(int p) {
    return (p - 1) / 2;
}

int left_heap_pos(int p) {
    return 2 * p + 1;
}

int right_heap_pos(int p) {
    return 2 * p + 2;
}

void swap_memnode(vector<MemNode *> &nodes, size_t fir_p, size_t sec_p) {
    MemNode *t = nodes[fir_p];
    nodes[fir_p] = nodes[sec_p];
    nodes[sec_p] = t;
    nodes[fir_p]->position = fir_p;
    nodes[sec_p]->position = sec_p;
}

void f_node_up(vector<MemNode *> &nodes, size_t pos) {
    while (parent_heap_pos(pos) >= 0 && compare(nodes[pos], nodes[parent_heap_pos(pos)])) {
        swap_memnode(nodes, parent_heap_pos(pos), pos);
        pos = parent_heap_pos(pos);
    }
}

void f_node_down(vector<MemNode *> &nodes, size_t pos) {
    while (true) {
        int nPos = pos;
        if (left_heap_pos(pos) < nodes.size() && compare(nodes[left_heap_pos(pos)], nodes[nPos])) {
            nPos = left_heap_pos(pos);
        }
        if (right_heap_pos(pos) < nodes.size() && compare(nodes[right_heap_pos(pos)], nodes[nPos])) {
            nPos = right_heap_pos(pos);
        }
        if (nPos == pos) {
            return;
        }
        swap_memnode(nodes, nPos, pos);
        pos = nPos;
    }
}

void del_node(vector<MemNode *> &nodes, size_t pos) {//not sure
    if (pos == nodes.size() - 1) {
        delete nodes[pos];
        nodes.pop_back();
        return;
    }

    swap_memnode(nodes, pos, nodes.size() - 1);
    delete nodes[nodes.size() - 1];
    nodes.pop_back();
    if (!nodes.empty() && pos < nodes.size()) {
        f_node_up(nodes, pos);
        f_node_down(nodes, pos);
    }
}

int main() {

    size_t mem_size;
    cin >> mem_size;
    size_t num_of_ord;
    cin >> num_of_ord;

    vector<MemNode *> used_mem(num_of_ord, nullptr);
    vector<MemNode *> free_mem;
    free_mem.reserve(num_of_ord);

    auto *fir = new MemNode(0, mem_size, true, nullptr, nullptr);
    fir->position = 0;
    free_mem.push_back(fir);

    for (int i = 0; i < num_of_ord; ++i) {
        int command;
        cin >> command;
        if (command > 0) {
            if (!free_mem.empty()) {
                auto *mem = free_mem[0];
                if (mem->size >= command) {
                    auto *mem_new = new MemNode(mem->start, command, false, mem->prev, mem);
                    used_mem[i] = mem_new;
                    mem->start += command;
                    mem->size -= command;
                    if (mem->size == 0) {//Удалить
                        mem->remove();
                        del_node(free_mem, mem->position);
                    } else {
                        f_node_down(free_mem, mem->position);
                    }
                    printf("%d\n", mem_new->start + 1);
                    continue;
                }
            }
            printf("%d\n", -1);
        } else {
            command = abs(command) - 1;
            if (used_mem[command] && !used_mem[command]->free) {
                auto *mem_freeing = used_mem[command];
                bool prev_free = mem_freeing->prev && mem_freeing->prev->free;
                bool next_free = mem_freeing->next && mem_freeing->next->free;
                mem_freeing->free = true;

                if (!(prev_free || next_free)) {
                    mem_freeing->position = free_mem.size();
                    free_mem.push_back(mem_freeing);
                    f_node_up(free_mem, mem_freeing->position);//
                } else {
                    if (!next_free) {//Поднять
                        auto flow = mem_freeing->prev;
                        mem_freeing->prev->size += mem_freeing->size;
                        mem_freeing->remove();
                        delete mem_freeing;
                        f_node_up(free_mem, flow->position);//
                    } else if (!prev_free) {//Поднять
                        auto flow = mem_freeing->next;
                        mem_freeing->next->size += mem_freeing->size;
                        mem_freeing->next->start = mem_freeing->start;
                        mem_freeing->remove();
                        delete mem_freeing;
                        f_node_up(free_mem, flow->position);//
                    } else {//Удалить
                        mem_freeing->prev->size += mem_freeing->next->size;
                        auto flow = mem_freeing->next;
                        mem_freeing->next->remove();
                        del_node(free_mem, flow->position);//
                        mem_freeing->prev->size += mem_freeing->size;
                        flow = mem_freeing->prev;
                        mem_freeing->remove();
                        delete mem_freeing;
                        f_node_up(free_mem, flow->position);
                    }
                }
                used_mem[command] = nullptr;
            }
        }
    }
}