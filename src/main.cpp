#include <algorithm>
#include <cstdio>
#include <iostream>
#include <sched.h>
#include <signal.h>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <filesystem>
#include "headers/builtin.hpp"
namespace fs = std::filesystem;


std::vector<std::string> split_args(std::string sen);
char *convert(const std::string &s);

int main(int argc, char *argv[]) {
  std::string input;
  const std::string exit_cmd = "exit";
  while (true) {
    std::cout << ">>> ";
    std::getline(std::cin, input);
    if (input == exit_cmd) {
      break;
    }
    std::vector<std::string> full_command = split_args(input);
    std::vector<char *> command_char;
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
      command_char.clear();
      for (char *ptr : command_char) {
        delete(ptr);
      }
      perror("Error");
    }
    // Parent Process
    else {
      wait(NULL);
    }
    //Deallocate all pointers
    for (char *ptr : command_char) {
      delete(ptr);
    }
  }

  return 0;
}
