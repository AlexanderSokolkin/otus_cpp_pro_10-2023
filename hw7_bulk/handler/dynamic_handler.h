#pragma once
#include "i_handler.h"



class DynamicHandler : public IHandler
{
public:
    DynamicHandler();
    ~DynamicHandler() override = default;

public:
    void init() override;
    void handle(const InputData& data) override;
    bool isComplete() override;

private:
    int m_startMarkCount;
    int m_endMarkCount;
};
