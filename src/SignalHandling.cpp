#include <csignal>
#include <unistd.h>
#include <stdlib.h>
#include "headers/SignalHandling.hpp"
#include "headers/Globals.hpp"


/// Uses SIGINT to interrupt the process
void SignalHandling::TerminateProcess([[maybe_unused]] int sig){
    kill(Globals::ChildPid, SIGINT);
}
