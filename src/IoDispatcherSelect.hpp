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
#ifndef _IO_DISPATCHER_SELECT_HPP_
#define _IO_DISPATCHER_SELECT_HPP_

#include <list>

#include "IIoDispatcher.hpp"

namespace reactor_example {

class IoDispatcherSelect:
        public IIoDispatcher
{
public:
    IoDispatcherSelect();
    virtual ~IoDispatcherSelect();

    virtual int init() override;
    virtual int dispatch() override;
    virtual int registerIoHandler(IIoHandler& handler) override;
    virtual int breakLoop() override;

private:
    int m_maxFd;
    bool m_isRunning;
    std::list<IIoHandler*> m_readIoHandlers;
};

}       // namespace
#endif  // _IO_DISPATCHER_SELECT_HPP_
