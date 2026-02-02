#pragma once

#include <string>

namespace BuiltIn {
  enum Commands { CD, PWD, EXIT, NOT_BUILTIN };
  Commands Convert(const std::string& str);
}

