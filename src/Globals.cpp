#include "headers/Globals.hpp"
#include <filesystem>
#include <format>
#include <string>
namespace fs = std::filesystem;


// Variable for ChildPID, used in TerminateProcess() to get the correct PID of the child process
int Globals::ChildPid = -1;
std::string Globals::HomeDir = std::format("/home/{}", getenv("USER"));
// Directory displayed to the user
std::string Globals::DisplayedDir = fs::current_path().string();


