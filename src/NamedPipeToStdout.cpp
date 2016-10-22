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
#include "NamedPipeToStdout.hpp"

#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>
#include <fcntl.h>

#include <iostream>


namespace reactor_example {

//--------------------------------------------------------------------------------------------
NamedPipeToStdout::NamedPipeToStdout(const std::string& name):
        m_pipePath(name),
        m_pipeIoHandle(-1)
{
}

//--------------------------------------------------------------------------------------------
NamedPipeToStdout::~NamedPipeToStdout()
{
    close(m_pipeIoHandle);
    unlink(m_pipePath.c_str());
}

//--------------------------------------------------------------------------------------------
int NamedPipeToStdout::init()
{
    if(mkfifo(m_pipePath.c_str(), S_IRWXU) < 0)
    {
        perror("mkfifo");
        return -1;
    }

    m_pipeIoHandle = open(m_pipePath.c_str(), O_RDWR | O_NONBLOCK);
    if(m_pipeIoHandle < 0)
    {
        perror("Open fifo");
        return -1;
    }

    return 0;
}

//--------------------------------------------------------------------------------------------
IoHandle NamedPipeToStdout::getIoHandle()
{
    return m_pipeIoHandle;
}

//--------------------------------------------------------------------------------------------
void NamedPipeToStdout::readReady()
{
    int buffSize = 64;
    char buffer[buffSize];
    ssize_t readSize;

    readSize = read(m_pipeIoHandle, buffer, buffSize);
    if(readSize < 0)
    {
        perror("Read from pipe");
        return;
    }

    if(write(1, buffer, readSize) < 0)
        perror("Write to stdout");
}

}       // namespace
