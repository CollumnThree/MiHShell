#include "headers/Builtin.hpp"
#include "headers/Globals.hpp"
#include "headers/Parser.hpp"
#include "headers/SignalHandling.hpp"
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <sched.h>
#include <signal.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
namespace fs = std::filesystem;

int main() {
  std::string Input;
  std::vector<char *> ArgV;
  signal(SIGINT, SignalHandling::TerminateProcess);
  while (true) {
    std::cout << Globals::DisplayedDir << ">>> ";
    std::getline(std::cin, Input);
    std::vector<std::string> FullCommand = Parser::SplitArgs(Input);
    // Check if the vector is empty
    if (FullCommand.empty()) {
      continue;
    }
    // Check if the inserted command is a builtin function(e.g: cd)
    switch (BuiltIn::Convert(FullCommand.at(0))) {
    case BuiltIn::CD:
      if (FullCommand.size() < 2) {
        if (chdir(Globals::HomeDir.c_str()) != 0) {
          perror("MiHShell: cd");
        } else {
          Globals::DisplayedDir = Globals::HomeDir;
        }
        continue;
      }
      if (chdir(FullCommand.at(1).c_str()) != 0) {
        perror("MiHShell: cd");
      } else {
        Globals::DisplayedDir = fs::current_path().string();
      }
      continue;
    case BuiltIn::PWD:
      std::cout << fs::current_path().string() << "\n";
      continue;
    case BuiltIn::EXIT:
      exit(0);
    case BuiltIn::NOT_BUILTIN:
      break;
    }
    // Insert the values into ArgV
    ArgV.reserve(FullCommand.size() + 1);
    for (auto &s : FullCommand) {
      ArgV.push_back(s.data());
    }
    // Push a nullptr to ArgV make it a null terminated string(For later
    // use in execvp)
    ArgV.push_back(nullptr);
    pid_t Command = fork();
    // If fork() fails
    if (Command < 0) {
      perror("MiHShell: fork");
      continue;
    }
    // Child Process
    else if (Command == 0) {
      execvp(FullCommand.at(0).c_str(), ArgV.data());
      perror("MiHShell");
      _exit(1);
    }
    // Parent Process
    else {
      Globals::ChildPid = Command;
      wait(NULL);
    }
    // Clear Vectors
    FullCommand.clear();
    ArgV.clear();
  }
  return 0;
}
