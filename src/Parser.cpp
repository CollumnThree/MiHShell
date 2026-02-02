#include <string>
#include <sstream>
#include <vector>
#include "headers/Parser.hpp"


//Splits the arguments from input(main.cpp) to a string vector of the arguments
    std::vector<std::string> Parser::SplitArgs(const std::string& sen) {
    std::stringstream ss(sen);
    std::string word;
    std::vector<std::string> words;
    while (ss >> word) {
        words.push_back(word);
    }
    return words;
}
