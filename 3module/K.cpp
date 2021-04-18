#include <iostream>
#include <list>

using namespace std;

struct MemPart {
public:
    int num;
    int start;
    int size;

    MemPart(int num_in, int start_in, int size_in) {
        num = num_in;
        start = start_in;
        size = size_in;
    }
};

int main() {
    int memorySize;
    cin >> memorySize;
    int numOfOrd;
    cin >> numOfOrd;

    list<MemPart> uses;
    list<MemPart> free;
    free.push_back(MemPart(0, 1, memorySize));

    for (int i = 0; i < numOfOrd; ++i) {
        int order;
        cin >> order;
        if (order > 0) {
            bool isAdded = false;
            for (auto mem = free.begin(); mem != free.end(); ++mem) {
                if (mem->size > order) {
                    MemPart mem_n = MemPart(i + 1, mem->start, order);
                    mem->start += order;
                    mem->size -= order;
                    uses.push_back(mem_n);
                    printf("%d\n", mem_n.start);
                    isAdded= true;
                    break;
                } else if (mem->size == order) {
                    MemPart mem_n = *mem;
                    free.erase(mem);
                    mem_n.num = i + 1;
                    uses.push_back(mem_n);
                    printf("%d\n", mem_n.start);
                    isAdded= true;
                    break;
                }
            }
            if (!isAdded) {
                printf("%d\n", -1);
            }

        } else {
            order = abs(order);
            MemPart memPart = MemPart(0, 0, 0);

            for (auto mem = uses.begin(); mem != uses.end(); ++mem) {
                if (mem->num == order) {
                    memPart = *mem;
                    uses.erase(mem);
                    break;
                }
            }

            int start = memPart.start;
            int size = memPart.size;



            if(size == 0){
                continue;
            }

            bool isPrev = false;
            auto prev = free.begin();
            bool isNext = false;
            auto next = free.begin();

            for (auto mem = free.begin(); mem != free.end(); ++mem) {
                if (mem->start + mem->size == start) {
                    memPart.start = mem->start;
                    memPart.size += mem->size;
                    prev = mem;
                    isPrev = true;
                } else if (start + size == mem->start) {
                    memPart.size += mem->size;
                    next = mem;
                    isNext = true;
                }
            }

            if(isPrev){
                free.erase(prev);
            }
            if(isNext){
                free.erase(next);
            }

            if (memPart.start + memPart.size > 0) {
                memPart.num = i + 1;
                free.push_back(memPart);
            }

        }
    }
}