#include "headers/Globals.hpp"
#include <string>
#include <format>
#include <filesystem>
namespace fs = std::filesystem;



int ChildPid = -1;
std::string HomeDir = std::format("/home/{}", getenv("USER"));
std::string DisplayedDir = fs::current_path().string();
