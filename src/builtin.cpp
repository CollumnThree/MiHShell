#include <string>
#include <map>
#include "headers/builtin.hpp"

//Takes the first position in the full_command vector and checks if fits a built-in function
bool IsBCommand(std::string str){
    std::map<std::string, bool> CommandDict;
    CommandDict["cd"] = true;
    CommandDict["pwd"] = true;
    CommandDict["exit"] = true;
    if(CommandDict[str] == true){
        return true;
    }
    else{
        return false;
    }
}


