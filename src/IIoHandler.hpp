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
#ifndef _I_IO_HANDLER_HPP_
#define _I_IO_HANDLER_HPP_

namespace reactor_example {

typedef int IoHandle;

class IIoHandler
{
public:
    IIoHandler();
    virtual ~IIoHandler();

    virtual IoHandle getIoHandle() = 0;
    virtual void readReady() = 0;
};

}       // namespace
#endif  // _I_IO_HANDLER_HPP_
