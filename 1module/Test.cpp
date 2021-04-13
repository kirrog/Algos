
#include <map>
#include <string>

int main(){
    std::map<std::string, int> variables;
    variables.insert_or_assign("B", 1);
    variables.insert_or_assign("B", 2);
    variables.insert_or_assign("B", 3);
    variables.erase("B");
    variables.insert_or_assign("B", 5);
    variables.insert_or_assign("B", 6);
}