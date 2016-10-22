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
#include <iostream>
#include <cassert>

#include "IoDispatcherSelect.hpp"

namespace reactor_example {

//--------------------------------------------------------------------------------------------
IoDispatcherSelect::IoDispatcherSelect():
        m_maxFd(-1),
        m_isRunning(false)
{
}

//--------------------------------------------------------------------------------------------
IoDispatcherSelect::~IoDispatcherSelect()
{
}

//--------------------------------------------------------------------------------------------
int IoDispatcherSelect::init()
{
    return 0;
}

//--------------------------------------------------------------------------------------------
int IoDispatcherSelect::dispatch()
{
    int ret = 0;

    m_isRunning = true;
    while(m_isRunning)
    {
        fd_set read_fds;
        int selectRes = 0;
        struct timeval timeout;

        FD_ZERO(&read_fds);

        for(auto& it: m_readIoHandlers)
        {
            int ioHandle = it->getIoHandle();

            assert(ioHandle >= 0);

            FD_SET(ioHandle, &read_fds);
        }

        timeout.tv_usec = 0;
        timeout.tv_sec = 1;
        selectRes = select(m_maxFd + 1, &read_fds, NULL, NULL, &timeout);
        if(selectRes < 0)
        {
            if(errno == EINTR)
                continue;
            else
            {
                perror("select");
                ret = -1;
                break;
            }
        }
        else if(selectRes == 0)
            continue;

        for(auto& it: m_readIoHandlers)
        {
            int ioHandle = it->getIoHandle();

            assert(ioHandle >= 0);

            if(FD_ISSET(ioHandle, &read_fds))
                it->readReady();
        }
    }

    return ret;
}

//--------------------------------------------------------------------------------------------
int IoDispatcherSelect::IoDispatcherSelect::registerIoHandler(IIoHandler& handler)
{
    if(handler.getIoHandle() > m_maxFd)
        m_maxFd = handler.getIoHandle();

    m_readIoHandlers.push_back(&handler);

    return 0;
}

//--------------------------------------------------------------------------------------------
int IoDispatcherSelect::breakLoop()
{
    m_isRunning = false;
    return 0;
}

}       // namespace
