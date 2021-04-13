#include "iostream"
#include "string"
#include "vector"
#include "map"

void compileHooks(std::vector<std::map<std::string, int>> *variablesIn, std::map<std::string, int> *listOfVariables) {

    std::map<std::string, int> variables;

    std::string str;
    while (std::cin >> str) {
        if (str == "{") {
            (*variablesIn).push_back(variables);
            compileHooks(variablesIn, listOfVariables);
        } else if (str == "}") {
            for (std::pair<std::string, int> pair : variables) {
                (*listOfVariables).insert_or_assign(pair.first, 0);
            }
            for (std::pair<std::string, int> pair : (*variablesIn).back()) {
                (*listOfVariables).insert_or_assign(pair.first, pair.second);
            }
            (*variablesIn).pop_back();
            return;
        } else {
            int equalId = str.find('=');
            std::string firstVar = str.substr(0, equalId);
            std::string secondVar = str.substr(equalId + 1, str.size());
            if (secondVar.find_first_not_of("-0123456789") == std::string::npos) {//Integer
                if (!(*variablesIn).empty() && (*variablesIn).back().count(firstVar) == 0 &&
                    (*listOfVariables).count(firstVar) > 0) {
                    ((*variablesIn).back()).insert_or_assign(firstVar, (*listOfVariables).at(firstVar));
                }
                (*listOfVariables).insert_or_assign(firstVar, std::stoi(secondVar));
                variables.insert_or_assign(firstVar, std::stoi(secondVar));
            } else {
                int i = 0;
                if ((*listOfVariables).count(secondVar) > 0) {
                    i = (*listOfVariables).at(secondVar);
                }
                if (!(*variablesIn).empty() && (*variablesIn).back().count(firstVar) == 0 &&
                    (*listOfVariables).count(firstVar) > 0) {
                    ((*variablesIn).back()).insert_or_assign(firstVar, (*listOfVariables).at(firstVar));
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
    std::vector<std::map<std::string, int>> variables;
    compileHooks(&variables, &listOfVariables);
    return 0;
}

