#include <string>
#include <sstream>
#include <vector>
#include "headers/utils.hpp"

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
