#include "headers/Globals.hpp"
#include "headers/SignalHandling.hpp"
#include "headers/Builtin.hpp"
#include "headers/Parser.hpp"
#include <cstdio>
#include <cstdlib>
#include <exception>
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
  signal(SIGINT, TerminateProcess);
  while (true) {
    std::cout << DisplayedDir << ">>> ";
    std::getline(std::cin, Input);
    std::vector<std::string> FullCommand = SplitArgs(Input);
    // Check if the vector is empty
    if (FullCommand.empty()) {
      continue;
    }
    // Check if the inserted command is a builtin function(e.g: cd)
    switch (Convert(FullCommand.at(0))) {
    case CD:
      if (FullCommand.size() < 2) {
        if (chdir(HomeDir.c_str()) != 0) {
          perror("MiHShell: cd");
        } else {
          DisplayedDir = HomeDir;
        }
        continue;
      }
      if (chdir(FullCommand.at(1).c_str()) != 0) {
        perror("MiHShell: cd");
      } else {
        DisplayedDir = fs::current_path().string();
      }
      continue;
    case PWD:
      std::cout << fs::current_path().string() << "\n";
      continue;
    case EXIT:
      exit(0);
    case NOT_BUILTIN:
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
      ChildPid = Command;
      
      wait(NULL);
    }
    // Clear Vectors
    FullCommand.clear();
    ArgV.clear();
  }
  return 0;
}
