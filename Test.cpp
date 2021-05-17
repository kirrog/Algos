//2module/E.cpp
#include <iostream>


int powerOfNumber(int num) {
    int size = num;
    int pow = 0;
    while (size > 0) {
        size = size >> 1;
        pow++;
    }
    if (num << 1 == 1 << pow) {
        pow--;
    }
    return pow;
}


int main() {

    for (int j = 2; j < 128; ++j) {
        printf("%d ", j);
        printf("%d\n", powerOfNumber(j));
    }


    return 0;
}