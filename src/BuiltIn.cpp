#include "headers/builtin.hpp"
#include <string>

Commands Convert(std::string str){
	if(str == "cd") return CD;
	else if(str == "pwd") return PWD;
	else if(str == "exit") return EXIT;
	else return NOT_BUILTIN;
}
