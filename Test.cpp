//2module/E.cpp

#include <vector>
#include <deque>
#include <string>

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
        this->prev = prev;
        this->next = next;
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
        MemPart *t = this->heapData[fir];
        this->heapData[fir] = this->heapData[sec];
        this->heapData[sec] = t;
        int tint = this->heapData[fir]->pos;
        this->heapData[fir]->pos = this->heapData[sec]->pos;
        this->heapData[sec]->pos = tint;
    }
};

// pos must be right
void CustomHeap::flowElemThrowHeap(int pos) {
    if (this->parent(pos) >= 0 && this->heapData[this->parent(pos)]->size < this->heapData[pos]->size) {
        while (this->parent(pos) >= 0 && this->heapData[this->parent(pos)]->size < this->heapData[pos]->size) {
            this->swapMemPart(this->parent(pos), pos);
            pos = this->parent(pos);
        }
    } else {
        if (this->right(pos) < this->heapData.size() &&
            this->heapData[this->right(pos)]->size > this->heapData[pos]->size) {
            while (this->right(pos) < this->heapData.size() &&
                   this->heapData[this->right(pos)]->size > this->heapData[pos]->size) {
                this->swapMemPart(this->right(pos), pos);
                pos = this->right(pos);
            }
        } else if (this->left(pos) < this->heapData.size() &&
                   this->heapData[this->left(pos)]->size > this->heapData[pos]->size) {
            while (this->left(pos) < this->heapData.size() &&
                   this->heapData[this->left(pos)]->size > this->heapData[pos]->size) {
                this->swapMemPart(this->left(pos), pos);
                pos = this->left(pos);
            }
        }
    }
}

void CustomHeap::popCustomHeap(int pos) {
    this->swapMemPart(pos, this->heapData.size() - 1);
    this->heapData.pop_back();
    this->flowElemThrowHeap(pos);
}

void CustomHeap::pushCustomHeap(MemPart *memPart) {
    memPart->pos = this->heapData.size();
    this->heapData.push_back(memPart);
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

    CustomHeap customHeap;



    return 0;
}