#include "i_handler.h"


IHandler::IHandler(HandlerType type) : m_type(type) {}

void IHandler::init()
{
    clear();
}


CommandBlock IHandler::getBlock() const
{
    return m_block;
}

CommandBlock&& IHandler::getBlock()
{
    return std::move(m_block);
}

void IHandler::clear()
{
    m_block.clear();
}

HandlerType IHandler::type() const
{
    return m_type;
}
