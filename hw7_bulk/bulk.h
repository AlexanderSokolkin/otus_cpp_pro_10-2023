#pragma once
#include "handler/i_handler.h"
#include "input/i_command_reader.h"
#include "output/i_block_writer.h"
#include "handler/handler_pool.h"
#include "arguments.h"
#include <memory>
#include <vector>



class Bulk
{
public:
    Bulk(const Arguments& args);

    int exec();

private:
    void writeCommandBlock();

private:
    HandlerPool m_pool;
    std::shared_ptr<IHandler> m_currentHandler;
    std::unique_ptr<ICommandReader> m_reader;
    std::vector<std::unique_ptr<IBlockWriter>> m_writers;
};
