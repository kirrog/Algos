//Увеличиваем участок взятых ордеров, пока не будет выполненно условие
//Что сумма кол-ва взятых парных и одиночных(считаются за один) и уже стоящих машинок, именно в ордере, а не на полу
//Равно числу умтановимых на пол элементов
#include <iostream>
#include <vector>

int main() {
    int cars;
    std::cin >> cars;
    int floorSize;
    std::cin >> floorSize;
    int order;
    std::cin >> order;
    int result = 0;

    if (cars > floorSize && order > floorSize) {
        std::vector<int> floor(floorSize);

        int pos = 0;
        for (int i = 0; i < order; ++i) {
            int in;
            std::cin >> in;

            for (int j = 0; j < floorSize; ++j) {
                if (floor[j] == in) {
                    break;
                }
            }

        }
    }

    printf("%d", result);

    return 0;
}
