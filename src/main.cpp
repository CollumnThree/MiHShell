#include "headers/KillProcess.hpp"
#include "headers/builtin.hpp"
#include "headers/utils.hpp"
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <format>
#include <iostream>
#include <map>
#include <sched.h>
#include <signal.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
namespace fs = std::filesystem;

const auto HomeDir = std::format("/home/{}", getenv("USER"));
auto CurrentDir = fs::current_path().string();

int main(int argc, char *argv[]) {
  std::string input;
  std::vector<char *> ArgV;
  while (true) {
    std::cout << CurrentDir << ">>> ";
    std::getline(std::cin, input);
    std::vector<std::string> FullCommand = split_args(input);
    // Pointer pointing to KillProcess function(for later use in signal())
    void (*KPPointer)(int);
    KPPointer = &KillProcess;
    // Check if the vector is empty
    if (FullCommand.empty()) {
      continue;
    }
    // Check if the inserted command is a builtin function(e.g: cd)
    if (IsBCommand(FullCommand.at(0)) == true) {
      auto &CommandList = BCommands;
      switch (CommandList[FullCommand.at(0)]) {
      case 1:
        if (FullCommand.size() < 2) {
          CurrentDir = HomeDir;
          chdir(HomeDir.c_str());
          continue;
        }
        chdir(FullCommand.at(1).c_str());
        CurrentDir = fs::current_path().string();
        continue;
      case 2:
        std::cout << fs::current_path().string() << "\n";
        continue;
      case 3:
        exit(0);
      }
    }
    // Insert the values into ArgV
    ArgV.reserve(FullCommand.size() + 1);
    for (auto &s : FullCommand) {
      ArgV.push_back(s.data()); 
    }
    // Push a nullptr to ArgV make it a null terminated string(For later
    // use in execvp)
    ArgV.push_back(nullptr);
    pid_t command = fork();
    // If fork() fails
    if (command < 0) {
      std::cout << "fork() fail \n";
      continue;
    }
    // Child Process
    else if (command == 0) {
      execvp(FullCommand.at(0).c_str(), ArgV.data());
      perror("MihShell");
      _exit(1);
    }
    // Parent Process
    else {
      ChildPid = command;
      signal(SIGINT, KPPointer);
      wait(NULL);
    }
    // Clear Vectors
    FullCommand.clear();
    ArgV.clear();
  }
  return 0;
}
