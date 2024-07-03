#include "dynamic_handler.h"
#include "input/input_data.h"


DynamicHandler::DynamicHandler() : IHandler(HandlerType::Dynamic) {}


void DynamicHandler::init()
{
    m_startMarkCount = 0;
    m_endMarkCount = 0;

    IHandler::init();
}

void DynamicHandler::handle(const InputData& data)
{
    switch (data.dataType) {
        case InputData::Type::StartDynamicSection:
            ++m_startMarkCount;
            break;
        case InputData::Type::EndDynamicSection:
            ++m_endMarkCount;
            break;
        case InputData::Type::Command:
            m_block.addCommand(data.command);
            break;
        default:
            break;
    }
}

bool DynamicHandler::isComplete()
{
    return m_startMarkCount == m_endMarkCount;
}

