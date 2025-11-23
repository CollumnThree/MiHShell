#include <algorithm>
#include <cstdio>
#include <exception>
#include <filesystem>
#include <iostream>
#include <map>
#include <ostream>
#include <sched.h>
#include <signal.h>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include "headers/utils.hpp"
#include "headers/builtin.hpp"
#include <filesystem>

int main(int argc, char *argv[]) {
  std::string input;
  while (true) {
    std::cout << ">>> ";
    std::getline(std::cin, input);
    std::vector<std::string> full_command = split_args(input);
    std::vector<char *> command_char;
    bool IsNBCommand = true;
    //Check if the inserted command is a builtin function(e.g: cd)
    if (IsBCommand(full_command.at(0)) == true) {
        IsNBCommand = false;
    }
    if (IsNBCommand == false) {
        std::map<std::string, int> CommandList = BCommands;
        switch (CommandList[full_command.at(0)]) {
            case 1:
                std::cout << "Not implemented\n";
                continue;
            case 2:
                std::cout << PWDFunc() << "\n";
                continue;

        }
    }
    // Converts full_command into a char * vector
    std::transform(full_command.begin(), full_command.end(),
                   std::back_inserter(command_char), convert);
    full_command.clear();
    //Push command_char a nullptr to make it a null terminated string
    command_char.push_back(nullptr);
    //Do a continue if the vector is empty
    if (command_char.at(0) == nullptr) {
        continue;
    }
    pid_t command = fork();
    //If fork() fails
    if (command < 0) {
      std::cout << "fork() fail \n";
      for (char *ptr : command_char) {
        delete(ptr);
      }
      command_char.clear();
    }
    // Child Process
    else if (command == 0) {
      execvp(command_char.at(0), command_char.data());
      perror("MihShell");
      _exit(1);
    }
    // Parent Process
    else {
      wait(NULL);
    }
    //Deallocate all pointers
    for (char *ptr : command_char) {
      delete(ptr);
    }
    command_char.clear();

  }

  return 0;
}
