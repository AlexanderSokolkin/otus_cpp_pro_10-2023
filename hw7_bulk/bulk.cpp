#include "bulk.h"
#include "input/command_reader_factory.h"
#include "output/block_writer_factory.h"
#include <iostream>



Bulk::Bulk(const Arguments& args) :
    m_pool(args.size),
    m_currentHandler(nullptr),
    m_reader(nullptr)
{
    m_currentHandler = m_pool.getHandler(HandlerType::Static);
    m_currentHandler->init();

    m_reader = CommandReaderFactory::createConsoleReader(std::cin);

    m_writers.push_back(BlockWriterFactory::createBasicOStreamWriter(std::cout));
    m_writers.push_back(BlockWriterFactory::createLogWriter(args.path.parent_path()));
}

int Bulk::exec()
{
    InputData data = m_reader->next();

    while (data.dataType != InputData::Type::EndOfFile) {
        if (data.dataType == InputData::Type::StartDynamicSection && m_currentHandler->type() == HandlerType::Static) {
            writeCommandBlock();
            m_currentHandler = m_pool.getHandler(HandlerType::Dynamic);
            m_currentHandler->init();
        }

        m_currentHandler->handle(data);

        if (m_currentHandler->isComplete()) {
            writeCommandBlock();
            if (m_currentHandler->type() == HandlerType::Dynamic) {
                m_currentHandler = m_pool.getHandler(HandlerType::Static);
                m_currentHandler->init();
            } else {
                m_currentHandler->clear();
            }
        }

        data = m_reader->next();
    }

    if (m_currentHandler->type() == HandlerType::Static) {
        writeCommandBlock();
    }

    return 0;
}

void Bulk::writeCommandBlock()
{
    for (auto& writer : m_writers) {
        writer->write(m_currentHandler->getBlock());
    }
}
