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
#ifndef _I_IO_DISPATCHER_HPP_
#define _I_IO_DISPATCHER_HPP_

#include "IIoHandler.hpp"

namespace reactor_example {

class IIoDispatcher
{
public:
    IIoDispatcher();
    virtual ~IIoDispatcher();

    virtual int init() = 0;
    virtual int dispatch() = 0;
    virtual int registerIoHandler(IIoHandler& handler) = 0;
    virtual int breakLoop() = 0;
};

}       // namespace
#endif  // _I_IO_DISPATCHER_HPP_
