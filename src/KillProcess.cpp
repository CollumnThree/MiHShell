#include <csignal>
#include <unistd.h>
#include <stdlib.h>
#include "headers/Globals.hpp"


void KillProcess([[maybe_unused]] int sig){
    kill(ChildPid, SIGTERM);
}
