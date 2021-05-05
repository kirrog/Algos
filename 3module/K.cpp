#include <iostream>
#include <deque>
#include <vector>

using namespace std;

struct MemPart {
    bool free;
    int start;
    int size;
    MemPart *next;
    MemPart *prev;

    MemPart(bool free, int start, int size, MemPart *prev, MemPart *next) {
        this->free = free;
        this->start = start;
        this->size = size;
        this->prev = prev;
        this->next = next;
    }

};


struct CustomHeap {
    vector<MemPart *> heapData;

    void makeHeapWithElem(int number);

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

    int findMemPartInHeap(MemPart *mem, int pos) {
        if (this->heapData[pos] && this->heapData[pos]->size > mem->size) {
            int left = findMemPartInHeap(mem, this->left(pos));
            int right = findMemPartInHeap(mem, this->right(pos));
            if (left != -1) {
                return left;
            } else if (right != -1) {
                return right;
            }
        } else {
            if (this->heapData[pos]->size == mem->size && this->heapData[pos]->start == mem->start) {
                return pos;
            }
        }
        return -1;
    }
};

//inserted at number place element swap to place to complete the heap condition
void CustomHeap::makeHeapWithElem(int number) {

    if (number != 0 && this->heapData[this->parent(number)]->size < this->heapData[number]->size) {
        while (number != 0 && this->heapData[this->parent(number)]->size < this->heapData[number]->size) {
            int parent = this->parent(number);
            swap((this->heapData[parent]), (this->heapData[number]));
            number = parent;
        }
    } else {
        while (number < this->heapData.size()) {
            if (this->heapData[this->left(number)]->size > this->heapData[number]->size) {
                int left = this->left(number);
                swap(this->heapData[left], this->heapData[number]);
                number = left;
            }
            if (this->heapData[this->right(number)]->size > this->heapData[number]->size) {
                int right = this->right(number);
                swap(this->heapData[right], this->heapData[number]);
                number = right;
            }
        }
    }
}

// mem goes to the bottom of the three and deleted there
void CustomHeap::deleteElemFromHeap(MemPart *mem) {
    int pos = findMemPartInHeap(mem, 0);
    swap(this->heapData[pos], this->heapData[this->heapData.size() - 1]);
    this->heapData.pop_back();
    makeHeapWithElem(pos);
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
                memPart->prev->prev->next = memPart;
                memPart->prev = memPart->prev->prev;
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
                memPart->next->next->prev = memPart;
                memPart->next = memPart->next->next;
            } else {
                memPart->next = nullptr;
            }

        }
    }
}

// adding used element in heap of free concatenate it with existed memory parts
void CustomHeap::addElemToHeap(MemPart *memPart) {
    transformUsedToFree(memPart);
    this->heapData.push_back(memPart);
    makeHeapWithElem(this->heapData.size() - 1);
}

// change size and start of mem on order value and update heap
void CustomHeap::upgradeElemInHeap(MemPart *mem, int order) {
    mem->start += order;
    mem->size -= order;
    if (mem->size == 0) {
        deleteElemFromHeap(mem);
    } else {
        int pos = findMemPartInHeap(mem, 0);
        makeHeapWithElem(pos);
    }
}

int main() {
    int memorySize;
    cin >> memorySize;
    int numOfOrd;
    cin >> numOfOrd;

    vector<MemPart *> useV(numOfOrd);

    CustomHeap customHeap;

    MemPart all = MemPart(true, 0, memorySize, nullptr, nullptr);
    customHeap.addElemToHeap(&all);

    for (int i = 0; i < numOfOrd; ++i) {

        int order;
        cin >> order;

        if (order > 0) {
            if (!customHeap.heapData.empty()) {
                MemPart *mem = customHeap.heapData[0];
                if (mem->size >= order) {

                    MemPart mem_n = MemPart(false, mem->start, order, mem->prev, mem->next);

                    if (mem->prev) {
                        mem->prev->next = &mem_n;
                    }

                    if (mem->size == order) {
                        if (mem->next) {
                            mem->next->prev = &mem_n;
                        }
                    } else {
                        mem_n.next = mem;
                    }

                    customHeap.upgradeElemInHeap(mem, order);
                    useV.push_back(&mem_n);
                    printf("%d\n", mem_n.start);
                    continue;
                }
            }
            useV.push_back(nullptr);
            printf("%d\n", -1);
        } else {
            order = abs(order);
            if (useV[order] == nullptr) {
                continue;
            }
            customHeap.addElemToHeap(useV[order]);
            useV[order] = nullptr;
        }
    }
}