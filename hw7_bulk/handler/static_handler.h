#pragma once
#include "i_handler.h"



class StaticHandler : public IHandler
{
public:
    StaticHandler(int size);
    ~StaticHandler() override = default;

public:
    void handle(const InputData& data) override;
    bool isComplete() override;

private:
    int m_size;
};
