//2module/E.cpp
#include <iostream>
#include <unordered_map>


int main() {

    std::unordered_map<long long, int> unorderedMap;

    for (int i = 0; i < 1000; ++i) {
        unorderedMap.insert(std::make_pair(i, i));
    }

    printf("%d", unorderedMap.begin()->first);


    return 0;
}