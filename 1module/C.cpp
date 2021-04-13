
#include "iostream"
#include "string"
#include "vector"
#include "map"

void compileHooks(std::map<std::string, int> *listOfVariables) {

    std::map<std::string, int> variables;
    std::map<std::string, int> prevVariables;

    std::string str;
    while (std::cin >> str) {
        if (str == "{") {
            compileHooks(listOfVariables);
        } else if (str == "}") {
            for (std::pair<std::string, int> pair : variables) {
                (*listOfVariables).erase(pair.first);
            }
            for (std::pair<std::string, int> pair : prevVariables) {
                (*listOfVariables).insert_or_assign(pair.first, pair.second);
            }
            return;
        } else {
            int equalId = str.find('=');
            std::string firstVar = str.substr(0, equalId);
            std::string secondVar = str.substr(equalId + 1, str.size());
            if (secondVar.find_first_not_of("-0123456789") == std::string::npos) {//Integer
                if (prevVariables.count(firstVar) == 0 && (*listOfVariables).count(firstVar) > 0 && variables.count(firstVar) == 0) {
                    prevVariables.insert_or_assign(firstVar, (*listOfVariables).at(firstVar));
                }
                (*listOfVariables).insert_or_assign(firstVar, std::stoi(secondVar));
                variables.insert_or_assign(firstVar, std::stoi(secondVar));
            } else {
                int i = 0;
                if (prevVariables.count(firstVar) == 0 && (*listOfVariables).count(firstVar) > 0 && variables.count(firstVar) == 0) {
                    prevVariables.insert_or_assign(firstVar, (*listOfVariables).at(firstVar));
                }
                if ((*listOfVariables).count(secondVar) > 0) {
                    i = (*listOfVariables).at(secondVar);
                }
                (*listOfVariables).insert_or_assign(firstVar, i);
                variables.insert_or_assign(firstVar, i);
                printf("%d\n", i);
            }
        }
    }
}

int main() {
    //Use list for maps
    std::map<std::string, int> listOfVariables;
    compileHooks(&listOfVariables);
    return 0;
}

