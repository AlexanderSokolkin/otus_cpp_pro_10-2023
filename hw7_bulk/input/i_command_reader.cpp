#include "i_command_reader.h"
#include "command.h"
#include <stdexcept>
#include <iostream>

ICommandReader::ICommandReader(ReaderType type) : m_type(type) {}


InputData ICommandReader::next()
{
    if (endData()) {
        return InputData{InputData::Type::EndOfFile};
    }

    if (!read()) {
        throw std::runtime_error("Data could not be read");
    }

    if (m_data == "{") {
        return InputData{InputData::Type::StartDynamicSection};
    } else if (m_data == "}") {
        return InputData{InputData::Type::EndDynamicSection};
    } else {
        return InputData{InputData::Type::Command, Command{m_data, m_timestamp}};
    }
}

ReaderType ICommandReader::type() const
{
    return m_type;
}
