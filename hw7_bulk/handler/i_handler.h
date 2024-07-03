#pragma once
#include "command.h"
#include "handler_type.h"


class InputData;


class IHandler
{
public:
    IHandler(HandlerType type);
    virtual ~IHandler() = default;

    CommandBlock getBlock() const;
    CommandBlock&& getBlock();
    void clear();
    HandlerType type() const;

public:
    virtual void init();
    virtual void handle(const InputData& data) = 0;
    virtual bool isComplete() = 0;

protected:
    CommandBlock m_block;
    HandlerType m_type;
};
