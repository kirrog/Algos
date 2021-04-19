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
            if (!free.empty()) {
                auto mem = free.begin();
                if (mem->size >= order) {
                    MemPart mem_n = MemPart(i + 1, mem->start, order);
                    mem->start += order;
                    mem->size -= order;
                    if (mem->size == 0) {
                        free.erase(mem);
                    } else {
                        MemPart memPart = *mem;
                        free.erase(mem);
                        bool isNameInsert = false;
                        memPart.num = i + 1;
                        for (auto mem_in = free.begin(); mem_in != free.end(); ++mem_in) {
                            if (mem_in->size <= memPart.size) {
                                free.insert(mem_in, memPart);
                                isNameInsert = true;
                                break;
                            }
                        }
                        if (!isNameInsert) {
                            free.push_back(memPart);
                        }
                    }
                    uses.push_back(mem_n);
                    printf("%d\n", mem_n.start);
                    continue;
                }
            }
            printf("%d\n", -1);
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


            if (size == 0) {
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

            if (isPrev) {
                free.erase(prev);
            }
            if (isNext) {
                free.erase(next);
            }

            if (memPart.start + memPart.size > 0) {
                bool isNameInsert = false;
                memPart.num = i + 1;
                for (auto mem = free.begin(); mem != free.end(); ++mem) {
                    if (mem->size <= memPart.size) {
                        free.insert(mem, memPart);
                        isNameInsert = true;
                        break;
                    }
                }
                if (!isNameInsert) {
                    free.push_back(memPart);
                }
            }
        }
    }
}