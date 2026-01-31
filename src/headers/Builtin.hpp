#pragma once

#include <string>

enum Commands { CD, PWD, EXIT, NOT_BUILTIN };
Commands Convert(const std::string& str);

