#include "headers/KillProcess.hpp"
#include "headers/builtin.hpp"
#include "headers/utils.hpp"
#include "headers/Globals.hpp"
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
    switch (Convert(FullCommand.at(0))) {
    case CD:
      if (FullCommand.size() < 2) {
        if (chdir(HomeDir.c_str()) != 0) {
          perror("MiHShell: cd");
        } else {
          CurrentDir = HomeDir;
        }
        continue;
      }
      if (chdir(FullCommand.at(1).c_str()) != 0) {
        perror("MiHShell: cd");
      } else {
        CurrentDir = fs::current_path().string();
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
