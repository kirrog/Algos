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

    void transformUsedToFree(MemPart *memPart);

    void flowElemThrowHeap(int pos);

    void popCustomHeap(int pos);

    void pushCustomHeap(MemPart *memPart);

    void swapMemPart(int fir, int sec) {
        MemPart *t = heapData[fir];
        heapData[fir] = heapData[sec];
        heapData[sec] = t;
        int tint = heapData[fir]->pos;
        heapData[fir]->pos = heapData[sec]->pos;
        heapData[sec]->pos = tint;
    }
};

// pos must be right
void CustomHeap::flowElemThrowHeap(int pos) {
    if (parent(pos) >= 0 && heapData[parent(pos)]->size < heapData[pos]->size) {
        while (parent(pos) >= 0 && heapData[parent(pos)]->size < heapData[pos]->size) {
            swapMemPart(parent(pos), pos);
            pos = parent(pos);
        }
    } else {
        if (left(pos) < heapData.size() &&
            heapData[left(pos)]->size > heapData[pos]->size) {
            while (left(pos) < heapData.size() &&
                   heapData[left(pos)]->size > heapData[pos]->size) {
                swapMemPart(left(pos), pos);
                pos = left(pos);
            }
        } else if (right(pos) < heapData.size() &&
                   heapData[right(pos)]->size > heapData[pos]->size) {
            while (right(pos) < heapData.size() &&
                   heapData[right(pos)]->size > heapData[pos]->size) {
                swapMemPart(right(pos), pos);
                pos = right(pos);
            }
        }
    }
}

void CustomHeap::popCustomHeap(int pos) {
    if (heapData.size() > 1 && pos < heapData.size() - 1) {
        swapMemPart(pos, heapData.size() - 1);
    }
    heapData.pop_back();
    if (!heapData.empty() && pos != heapData.size()) {
        flowElemThrowHeap(pos);
    }
}

void CustomHeap::pushCustomHeap(MemPart *memPart) {
    memPart->pos = heapData.size();
    heapData.push_back(memPart);
    flowElemThrowHeap(memPart->pos);
}


// mem goes to the bottom of the three and deleted there
void CustomHeap::deleteElemFromHeap(MemPart *mem) {
    int pos = mem->pos;
    popCustomHeap(pos);
}

// used memPart concatenate with neighbors
void CustomHeap::transformUsedToFree(MemPart *memPart) {
    memPart->free = true;
    if (memPart->prev) {
        if (memPart->prev->free) {
            deleteElemFromHeap(memPart->prev);
            memPart->start = memPart->prev->start;
            memPart->size += memPart->prev->size;
            if (memPart->prev->prev) {
                MemPart *memPrev = memPart->prev->prev;
                memPrev->next = memPart;
                memPart->prev = memPrev;
            } else {
                memPart->prev = nullptr;
            }
        }
    }
    if (memPart->next) {
        if (memPart->next->free) {
            deleteElemFromHeap(memPart->next);
            memPart->size += memPart->next->size;
            if (memPart->next->next) {
                MemPart *memNext = memPart->next->next;
                memNext->prev = memPart;
                memPart->next = memNext;
            } else {
                memPart->next = nullptr;
            }
        }
    }
}

// used in main
// adding used element in heap of free concatenate it with existed memory parts
void CustomHeap::addElemToHeap(MemPart *memPart) {
    transformUsedToFree(memPart);
    pushCustomHeap(memPart);
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
        flowElemThrowHeap(pos);
    }
}

int main() {

    int memorySize;
    cin >> memorySize;
    int numOfOrd;
    cin >> numOfOrd;


    vector<MemPart> usedMem(numOfOrd, MemPart(true, -1, -1));
    CustomHeap customHeap;

    MemPart all = MemPart(true, 0, memorySize);
    customHeap.addElemToHeap(&all);

    for (int i = 0; i < numOfOrd; ++i) {

        int order;
        cin >> order;

        if (order > 0) {
            if (!customHeap.heapData.empty()) {
                MemPart *mem = customHeap.heapData[0];
                if (mem->size >= order) {

                    usedMem[i] = MemPart(false, mem->start, order);

                    MemPart *memPointer = &usedMem[i];

                    if (mem->prev) {
                        memPointer->prev = mem->prev;
                        mem->prev->next = memPointer;
                    }

                    if (mem->size == order) {
                        if (mem->next) {
                            memPointer->next = mem->next;
                            mem->next->prev = memPointer;
                        }
                    } else {
                        memPointer->next = mem;
                        mem->prev = memPointer;
                    }

                    customHeap.upgradeElemInHeap(mem, order);

                    printf("%d\n", memPointer->start + 1);
                    continue;
                }
            }

            printf("%d\n", -1);
        } else {
            order = abs(order) - 1;
            if (!usedMem[order].free) {
                customHeap.addElemToHeap(&usedMem[order]);
            }
        }
    }
}