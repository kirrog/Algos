//2module/E.cpp
#include <iostream>


int main() {

    int res = 9;
    for (int i = 1; i < res + 1; ++i) {
        for (int j = 1; j < res + 1; ++j) {
            if (i < j) {
                printf("%d %d\n", i, j);
            }
        }
    }


    return 0;
}