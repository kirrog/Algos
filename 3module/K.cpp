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

    MemPart(bool free, int start, int size) {
        this->free = free;
        this->start = start;
        this->size = size;
        pos = -1;
        prev = nullptr;
        next = nullptr;
    }

};

void linkingMemParts(MemPart *left, MemPart *right) {
    if (left) {
        left->next = right;
    }
    if (right) {
        right->prev = left;
    }
}


struct CustomHeap {
    vector<MemPart *> heapData;

    void deleteElemFromHeap(MemPart *mem);

    void addElemToHeap(MemPart *memPart);

    void upgradeElemInHeap(MemPart *mem, int order);

    int parent(int num) {
        return (num - 1) / 2;
    }

    int left(int num) {
        return 2 * num + 1;
    }

    int right(int num) {
        return 2 * num + 2;
    }

    bool transformUsedToFree(MemPart *memPart);

    void flowUp(int pos);

    void flowDown(int pos);

    void popCustomHeap(int pos);

    void pushCustomHeap(MemPart *memPart);

    void swapMemPart(int firPos, int secPos) {
        MemPart *t = heapData[firPos];
        heapData[firPos] = heapData[secPos];
        heapData[secPos] = t;
        int tint = heapData[firPos]->pos;
        heapData[firPos]->pos = heapData[secPos]->pos;
        heapData[secPos]->pos = tint;
    }

};

void CustomHeap::flowUp(int pos) {
    while (parent(pos) >= 0 && heapData[parent(pos)]->size < heapData[pos]->size) {
        swapMemPart(parent(pos), pos);
        pos = parent(pos);
    }
}

void CustomHeap::flowDown(int pos) {
    bool leftPos = left(pos) < heapData.size() &&
                heapData[left(pos)]->size > heapData[pos]->size;
    bool rightPos = right(pos) < heapData.size() &&
                    heapData[right(pos)]->size > heapData[pos]->size;
    while (left(pos) < heapData.size() &&
           heapData[left(pos)]->size > heapData[pos]->size ||
           right(pos) < heapData.size() &&
           heapData[right(pos)]->size > heapData[pos]->size) {
        if (left(pos) < heapData.size() &&
            heapData[left(pos)]->size > heapData[pos]->size &&
            right(pos) < heapData.size() &&
            heapData[right(pos)]->size > heapData[pos]->size) {
            if (heapData[left(pos)]->size < heapData[right(pos)]->size) {
                swapMemPart(right(pos), pos);
                pos = right(pos);
            } else {
                swapMemPart(left(pos), pos);
                pos = left(pos);
            }
        } else if (left(pos) < heapData.size() &&
                   heapData[left(pos)]->size > heapData[pos]->size) {
            swapMemPart(left(pos), pos);
            pos = left(pos);
        } else if (right(pos) < heapData.size() &&
                   heapData[right(pos)]->size > heapData[pos]->size) {
            swapMemPart(right(pos), pos);
            pos = right(pos);
        }
        leftPos = left(pos) < heapData.size() &&
                  heapData[left(pos)]->size > heapData[pos]->size;
        rightPos = right(pos) < heapData.size() &&
                   heapData[right(pos)]->size > heapData[pos]->size;
    }
}

void CustomHeap::popCustomHeap(int pos) {
    if (heapData.size() > 1 && pos < heapData.size() - 1) {
        swapMemPart(pos, heapData.size() - 1);
    }
    heapData.pop_back();
    if (!heapData.empty() && pos < heapData.size()) {
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

bool CustomHeap::transformUsedToFree(MemPart *memPart) {
    memPart->free = true;
    bool res = true;

    if (memPart->prev) {
        if (memPart->prev->free) {
            memPart->prev->size += memPart->size;
            res = false;
            if (memPart->next) {
                MemPart *memPrev = memPart->prev;
                memPrev->next = memPart->next;
                memPart->next->prev = memPrev;
            } else {
                memPart->prev->next = nullptr;
                flowUp(memPart->prev->pos);
                delete memPart;
                return res;
            }
        }
    }
    if (memPart->next) {
        if (memPart->next->free) {
            if (res) {
                res = false;
                memPart->next->size += memPart->size;
                memPart->next->start = memPart->start;
                if (memPart->prev) {
                    MemPart *memNext = memPart->next;
                    memNext->prev = memPart->prev;
                    memPart->prev->next = memNext;
                } else {
                    memPart->next->prev = nullptr;
                }
                flowUp(memPart->next->pos);
            } else {
                memPart->prev->size += memPart->next->size;
                if (memPart->next->next) {
                    MemPart *memPrev = memPart->prev;
                    memPrev->next = memPart->next->next;
                    memPart->next->next->prev = memPrev;
                } else {
                    memPart->prev->next = nullptr;
                }
                deleteElemFromHeap(memPart->next);
                flowUp(memPart->prev->pos);
            }
            delete memPart;
        } else {
            if (!res) {
                delete memPart;
            }
        }
    }
    return res;
}

// used in main
// adding used element in heap of free concatenate it with existed memory parts
void CustomHeap::addElemToHeap(MemPart *memPart) {
    bool hasntNeighbours = transformUsedToFree(memPart);
    if (hasntNeighbours) {
        pushCustomHeap(memPart);
    }
}

// used in main
// change size and start of mem on order value and update heap
void CustomHeap::upgradeElemInHeap(MemPart *mem, int order) {
    mem->start += order;
    mem->size -= order;
    if (mem->size == 0) {
        deleteElemFromHeap(mem);
    } else {
        int pos = mem->pos;
        flowDown(pos);
    }
}

int main() {

    int memorySize;
    cin >> memorySize;
    int numOfOrd;
    cin >> numOfOrd;

    vector<MemPart *> usedMem(numOfOrd, nullptr);
    CustomHeap customHeap;

    MemPart *all = new MemPart(true, 0, memorySize);
    customHeap.addElemToHeap(all);

    for (int i = 0; i < numOfOrd; ++i) {

        int order;
        cin >> order;

        if (order > 0) {
            if (!customHeap.heapData.empty()) {
                MemPart *mem = customHeap.heapData[0];
                if (mem->size >= order) {

                    usedMem[i] = new MemPart(false, mem->start, order);

                    MemPart *memPointer = usedMem[i];

                    linkingMemParts(mem->prev, memPointer);

                    mem->prev = memPointer;

                    if (mem->size == order) {
                        linkingMemParts(memPointer, mem->next);
                    } else {
                        memPointer->next = mem;
                    }

                    customHeap.upgradeElemInHeap(mem, order);

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