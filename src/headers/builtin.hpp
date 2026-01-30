#ifndef BUILTIN_H
#define BUILTIN_H

#include <string>

enum Commands { CD, PWD, EXIT, NOT_BUILTIN };
Commands Convert(std::string str);

#endif
