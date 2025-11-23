#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include "headers/utils.hpp"


//Converts a string vector into a char pointer vector
char *convert(const std::string & s) {
   char *pc = new char[s.size()+1];
   std::strcpy(pc, s.c_str());
   return pc;
}

//Splits the arguments from input(main.cpp) to a string vector(full_command)
std::vector<std::string> split_args(std::string sen) {
    std::stringstream ss(sen);
    std::string word;
    std::vector<std::string> words;
    while (ss >> word) {
        words.push_back(word);
    }
    return words;
}
