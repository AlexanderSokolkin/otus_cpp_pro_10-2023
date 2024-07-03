#include "static_handler.h"
#include "input/input_data.h"



StaticHandler::StaticHandler(int size) : IHandler(HandlerType::Static), m_size(size) {}

void StaticHandler::handle(const InputData& data)
{
    m_block.addCommand(data.command);
}

bool StaticHandler::isComplete()
{
    return m_block.size() == m_size;
}
