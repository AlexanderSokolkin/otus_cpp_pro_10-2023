#pragma once
#include "handler_type.h"
#include "i_handler.h"
#include <map>
#include <memory>



class HandlerPool
{
public:
    HandlerPool() = default;
    HandlerPool(int staticHandlerSize);

    std::shared_ptr<IHandler> getHandler(HandlerType type);
    void addHandler(HandlerType type, std::shared_ptr<IHandler> handler);

private:
    std::map<HandlerType, std::shared_ptr<IHandler>> m_pool;
};
