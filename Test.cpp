//2module/E.cpp
#include <iostream>


int main() {

    int res = 0;
    for (int i = 1; i <= 6; ++i) {
        for (int j = 1; j <= 6; ++j) {
            if ((j + i) % 3 == 0) {
                res++;
            }
        }
    }


    return res;
}