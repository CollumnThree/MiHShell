#pragma once

#include <csignal>
#include <unistd.h>
#include <stdlib.h>
#include "headers/SignalHandling.hpp"

/// Uses SIGINT to interrupt the process
void TerminateProcess([[maybe_unused]] int sig){
    kill(ChildPid, SIGINT);
}
