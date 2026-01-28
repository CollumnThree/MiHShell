#ifndef BUILTIN_H
#define BUILTIN_H


#include <map>
#include <string>

bool IsBCommand(std::string str);
inline std::map<std::string, int> BCommands= {
    {"cd", 1},
    {"pwd", 2},
    {"exit", 3}
};
#endif
