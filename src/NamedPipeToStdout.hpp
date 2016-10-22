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
#ifndef _NAMED_PIPE_TO_STDOUT_HPP_
#define _NAMED_PIPE_TO_STDOUT_HPP_

#include <string>

#include "IIoDispatcher.hpp"

namespace reactor_example {

class NamedPipeToStdout:
        public IIoHandler
{
public:
    NamedPipeToStdout(const std::string& name);
    virtual ~NamedPipeToStdout();

    int init();

    virtual IoHandle getIoHandle() override;
    virtual void readReady() override;

private:
    std::string m_pipePath;
    IoHandle m_pipeIoHandle;
};

}       // namespace
#endif  // _NAMED_PIPE_TO_STDOUT_HPP_
