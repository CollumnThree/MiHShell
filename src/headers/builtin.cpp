#include <map>
#include <string>

bool IsBuiltin(int arg){
    std::map<std::string, int> commands;
    switch (arg) {
        case 1:
            return true;
        case 2:
            return true;
        default:
            return false;
    }
}
