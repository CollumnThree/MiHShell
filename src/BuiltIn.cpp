#include "headers/Builtin.hpp"
#include <string>


// Command for checking if inserted string matches one of the built-in commands
BuiltIn::Commands BuiltIn::Convert(const std::string& str){
	if(str == "cd") return CD;
	else if(str == "pwd") return PWD;
	else if(str == "exit") return EXIT;
	else return NOT_BUILTIN;
}
