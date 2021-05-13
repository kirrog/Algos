#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

struct MemPart {

    bool free;
    int start;
    int size;
    int pos;
    MemPart *next;
    MemPart *prev;

    MemPart(bool free, int start, int size, MemPart *prev, MemPart *next) {
        this->free = free;
        this->start = start;
        this->size = size;
        pos = -1;
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
        if (next) {
            next->prev = prev;
        }
        if (prev) {
            prev->next = next;
        }
    }

};

struct CustomHeap {
    vector<MemPart *> heapData;

    void deleteElemFromHeap(MemPart *mem);

    void addElemToHeap(MemPart *memPart);

    int parent(int num) {
        return (num - 1) / 2;
    }

    int left(int num) {
        return 2 * num + 1;
    }

    int right(int num) {
        return 2 * num + 2;
    }

    void flowUp(int pos);

    void flowDown(int pos);

    void popCustomHeap(int pos);

    void pushCustomHeap(MemPart *memPart);

    void swapMemPart(int firPos, int secPos) {
        MemPart *t = heapData[firPos];
        heapData[firPos] = heapData[secPos];
        heapData[secPos] = t;
        heapData[firPos]->pos = firPos;
        heapData[secPos]->pos = secPos;
    }

    bool compare(int posHigher, int posLess) {
        return heapData[posHigher]->size > heapData[posLess]->size;
    }

};

void CustomHeap::flowUp(int pos) {
    while (parent(pos) >= 0 && compare(pos, parent(pos))) {
        swapMemPart(parent(pos), pos);
        pos = parent(pos);
    }
}

void CustomHeap::flowDown(int pos) {
    while (true) {
        int nPos = pos;
        if (left(pos) < heapData.size() && compare(left(pos), nPos)) {
            nPos = left(pos);
        }
        if (right(pos) < heapData.size() && compare(right(pos), nPos)) {
            nPos = right(pos);
        }
        if (nPos == pos) {
            return;
        }
        swapMemPart(nPos, pos);
        pos = nPos;
    }
}

void CustomHeap::popCustomHeap(int pos) {
    if (heapData.size() > 1 && pos < heapData.size() - 1) {
        swapMemPart(pos, heapData.size() - 1);
    }
    heapData.pop_back();
    if (!heapData.empty() && pos < heapData.size()) {
        flowUp(pos);
        flowDown(pos);
    }
}

void CustomHeap::pushCustomHeap(MemPart *memPart) {
    memPart->pos = heapData.size();
    heapData.push_back(memPart);
    flowUp(memPart->pos);
}

void CustomHeap::deleteElemFromHeap(MemPart *mem) {
    int pos = mem->pos;
    popCustomHeap(pos);
    delete mem;
}

void CustomHeap::addElemToHeap(MemPart *memPart) {
    memPart->free = true;

    bool prevFree = memPart->prev && memPart->prev->free;
    bool nextFree = memPart->next && memPart->next->free;

    if (!(prevFree || nextFree)) {
        pushCustomHeap(memPart);
        return;
    }
    if (!nextFree) {
        memPart->prev->size += memPart->size;
        flowUp(memPart->prev->pos);
        memPart->remove();
        delete memPart;
        return;
    }
    if (!prevFree) {
        memPart->next->size += memPart->size;
        memPart->next->start = memPart->start;
        flowUp(memPart->next->pos);
        memPart->remove();
        delete memPart;
        return;
    }

    memPart->prev->size += memPart->next->size;
    MemPart *ne = memPart->next;
    memPart->next->remove();
    deleteElemFromHeap(ne);
    memPart->prev->size += memPart->size;
    flowUp(memPart->prev->pos);
    memPart->remove();
    delete memPart;
}

int main() {

    int memorySize;
    cin >> memorySize;
    int numOfOrd;
    cin >> numOfOrd;

    vector<MemPart *> usedMem(numOfOrd, nullptr);
    CustomHeap customHeap;

    MemPart *all = new MemPart(true, 0, memorySize, nullptr, nullptr);
    customHeap.pushCustomHeap(all);

    for (int i = 0; i < numOfOrd; ++i) {

        int order;
        cin >> order;

        if (order > 0) {
            if (!customHeap.heapData.empty()) {
                MemPart *mem = customHeap.heapData[0];
                if (mem->size >= order) {

                    MemPart *memPointer = new MemPart(false, mem->start, order, mem->prev, mem);
                    usedMem[i] = memPointer;

                    mem->start += order;
                    mem->size -= order;
                    if (mem->size == 0) {
                        mem->remove();
                        customHeap.deleteElemFromHeap(mem);
                    } else {
                        customHeap.flowDown(mem->pos);
                    }

                    printf("%d\n", memPointer->start + 1);
                    continue;
                }
            }

            printf("%d\n", -1);
        } else {
            order = abs(order) - 1;
            if (usedMem[order]) {
                if (!usedMem[order]->free) {
                    customHeap.addElemToHeap(usedMem[order]);
                    usedMem[order] = nullptr;
                }
            }
        }

    }


}