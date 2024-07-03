#pragma once
#include "input_data.h"
#include "reader_type.h"
#include <string>
#include <chrono>



class ICommandReader
{
public:
    ICommandReader(ReaderType type);
    virtual ~ICommandReader() = default;

    InputData next();
    ReaderType type() const;

protected:
    virtual bool read() = 0;
    virtual bool endData() = 0;


protected:
    ReaderType m_type;
    std::string m_data;
    std::chrono::time_point<std::chrono::system_clock> m_timestamp;
};

