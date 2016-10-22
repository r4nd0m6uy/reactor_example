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
#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

bool isRunning = false;

//--------------------------------------------------------------------------------------------
void onSignal(int signum, siginfo_t *info, void *ptr)
{
    std::cout << "Reived signal " << signum << " breaking loop!" << std::endl;
    isRunning = false;
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
    std::string fifoPath = "/tmp/test_pipe";
    int ret;
    int fifoFd;

    if(mkfifo(fifoPath.c_str(), S_IRWXU) < 0)
    {
        if(errno != EEXIST)
        {
            perror("mkfifo");
            return -1;
        }
    }

    fifoFd = open(fifoPath.c_str(), O_RDONLY | O_NONBLOCK);
    if(fifoFd < 0)
    {
        perror("Open fifo");
        unlink(fifoPath.c_str());
        return -1;
    }

    if(signalInit())
    {
        unlink(fifoPath.c_str());
        close(fifoFd);
        return -1;
    }

    isRunning = true;
    while(isRunning)
    {
        int buffSize = 256;
        char buffer[buffSize];
        ssize_t readSize;

        readSize = read(fifoFd, buffer, buffSize);
        if(readSize < 0)
        {
            if(errno == EAGAIN || errno == EWOULDBLOCK)
                continue;
            else
            {
                perror("Read from pipe");
                ret = -1;
                break;
            }
        }

        if(write(1, buffer, readSize) < 0)
        {
            perror("Write to stdout");
            ret = -1;
            break;
        }
    }

    close(fifoFd);
    unlink(fifoPath.c_str());
    return ret;
}
