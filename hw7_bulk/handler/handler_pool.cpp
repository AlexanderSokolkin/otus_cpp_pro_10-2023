#include "handler_pool.h"
#include "static_handler.h"
#include "dynamic_handler.h"
#include "handler_type.h"



HandlerPool::HandlerPool(int staticHandlerSize)
{
    m_pool.insert(std::pair(HandlerType::Static,
                            std::shared_ptr<StaticHandler>(new StaticHandler(staticHandlerSize))));

    m_pool.insert(std::pair(HandlerType::Dynamic,
                            std::shared_ptr<DynamicHandler>(new DynamicHandler())));
}


std::shared_ptr<IHandler> HandlerPool::getHandler(HandlerType type)
{
    auto it = m_pool.find(type);
    if (it == m_pool.end()) {
        return std::shared_ptr<IHandler>(nullptr);
    }

    return it->second;
}

void HandlerPool::addHandler(HandlerType type, std::shared_ptr<IHandler> handler)
{
    m_pool[type] = handler;
}
