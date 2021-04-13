
#include <vector>
#include <string>
#include <iostream>

int main() {

    std::string strIn;
    std::cin >> strIn;

    std::vector<int> charsWeights(26, 0);

    std::vector<int> charsNumber(26, 0);
    std::vector<char> chars(26, 0);

    int count = strIn.size();

    for (int i = 0; i < count; ++i) {
        charsNumber[strIn.at(i) - 97] += 1;
    }

    for (int i = 0; i < 26; ++i) {
        std::cin >> charsWeights[i];
    }

    for (int i = 0; i < 26; ++i) {
        int max = -1;
        int index = -1;
        for (int j = 0; j < 26; ++j) {
            if (max < charsWeights[j]) {
                max = charsWeights[j];
                index = j;
            }
        }
        chars[i] = (char) (index + 97);
        charsWeights[index] = -1;
    }

    std::vector<int> charsMiddle(26, 0);

    for (int i = 0; i < 26; ++i) {
        if (charsNumber[chars[i] - 97] > 2) {
            charsMiddle.at(chars[i] - 97) = charsNumber[chars[i] - 97] - 2;
            charsNumber[chars[i] - 97] = 1;
            printf("%c", chars[i]);
        } else if (charsNumber[chars[i] - 97] == 2) {
            charsNumber[chars[i] - 97] = 1;
            printf("%c", chars[i]);
        } else if (charsNumber[chars[i] - 97] == 1) {
            charsNumber[chars[i] - 97] = 0;
            charsMiddle.at(chars[i] - 97) = 1;
        }
    }

    for (int i = 0; i < 26; ++i) {
        int size = charsMiddle[chars[i] - 97];
        for (int j = 0; j < size; ++j) {
            printf("%c", chars[i]);
        }
    }

    for (int i = 25; i >= 0; i--) {
        if (charsNumber[chars[i] - 97] == 1) {
            printf("%c", chars[i]);
        }
    }

    return 0;
}