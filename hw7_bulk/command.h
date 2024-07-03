#pragma once
#include <list>
#include <string>
#include <chrono>


struct Command
{
    std::string name;
    std::chrono::time_point<std::chrono::system_clock> timestamp;
};



class CommandBlock
{
public:
    void clear();
    size_t size() const;
    bool empty() const;
    void addCommand(const Command& cmd);
    const Command& front() const;

    bool iter_next() const;
    void iter_resetCounter() const;
    const Command& iter_command() const;

private:
    std::list<Command> m_commands;

    mutable decltype(m_commands.cbegin()) it;
    mutable int index = 0;
};
