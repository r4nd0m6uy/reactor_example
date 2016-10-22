/**
 * DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                     Version 2, December 2004
 * Copyright (C) 2016 R4nd0m6uy <r4nd0m6uy@r4nd0m6uy.ch>
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
 */
#include <signal.h>
#include <string.h>

#include <iostream>

#include "IoDispatcherSelect.hpp"
#include "NamedPipeToStdout.hpp"

using namespace reactor_example;

IoDispatcherSelect mainLoop;

//--------------------------------------------------------------------------------------------
void onSignal(int signum, siginfo_t *info, void *ptr)
{
    std::cout << "Reived signal " << signum << " breaking loop!" << std::endl;

    mainLoop.breakLoop();
}

//--------------------------------------------------------------------------------------------
int signalInit()
{
    struct sigaction act;

    memset(&act, 0, sizeof(act));
    act.sa_sigaction = onSignal;
    act.sa_flags = SA_SIGINFO;

    if(sigaction(SIGTERM, &act, NULL) ||
        sigaction(SIGINT, &act, NULL))
    {
        perror("sigaction");
        return -1;
    }

    return 0;
}

//--------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    NamedPipeToStdout pipe1("/tmp/test_pipe1");
    NamedPipeToStdout pipe2("/tmp/test_pipe2");

    if(signalInit())
        return -1;
    if(mainLoop.init())
        return -1;
    if(pipe1.init())
        return -1;
    if(pipe2.init())
        return -1;

    mainLoop.registerIoHandler(pipe1);
    mainLoop.registerIoHandler(pipe2);

    return mainLoop.dispatch();
}
