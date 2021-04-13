#include "iostream"
#include "string"
#include "vector"
#include "map"

void compileHooks(std::vector<std::map<std::string, int>> *variablesIn, int level) {
    std::map<std::string, int> variables;
    std::string str;
    while (std::cin >> str) {
        if (str.size() == 1) {
            if (str == "{") {
                (*variablesIn).push_back(variables);
                compileHooks(variablesIn, level + 1);
            } else if (str == "}") {
                (*variablesIn).pop_back();
                return;
            }
        } else {
            int equalId = str.find('=');
            std::string first;
            std::string second;
            first = str.substr(0, equalId);
            second = str.substr(equalId + 1, str.size());
            if (second.find_first_not_of("-0123456789") == std::string::npos) {//Integer
                variables.insert_or_assign(first, std::stoi(second));
            } else {
                int i = 0;
                if (variables.count(second) > 0) {
                    i = variables.at(second);
                } else {
                    for (int j = level - 1; j >= 0; --j) {
                        if ((*variablesIn)[j].count(second) > 0) {
                            i = (*variablesIn)[j].at(second);
                            break;
                        }
                    }
                }
                variables.insert_or_assign(first, i);
                printf("%d\n", i);
            }
        }
    }
}

int main() {
    std::vector<std::map<std::string, int>> variables;
    compileHooks(&variables, 0);
    return 0;
}

