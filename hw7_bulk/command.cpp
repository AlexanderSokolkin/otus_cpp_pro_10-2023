#include "command.h"



void CommandBlock::clear()
{
    m_commands.clear();
    iter_resetCounter();
}

size_t CommandBlock::size() const
{
    return m_commands.size();
}

bool CommandBlock::empty() const
{
    return m_commands.empty();
}

void CommandBlock::addCommand(const Command& cmd)
{
    m_commands.push_back(cmd);
    iter_resetCounter();
}

const Command& CommandBlock::front() const
{
    return m_commands.front();
}  

bool CommandBlock::iter_next() const
{
    if (size() == index) {
        return false;
    }

    if (index == 0) {
        it = m_commands.cbegin();
    } else {
        ++it;
    }

    ++index;

    return true;
}

void CommandBlock::iter_resetCounter() const
{
    index = 0;
}

const Command& CommandBlock::iter_command() const
{
    return *it;
}
