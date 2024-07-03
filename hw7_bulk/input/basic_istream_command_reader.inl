// #include "basic_istream_command_reader.h"
#include <iostream>


template <typename Elem, typename Traits>
BasicIStreamCommandReader<Elem, Traits>::BasicIStreamCommandReader(std::basic_istream<Elem, Traits>& stream) :
    ICommandReader(ReaderType::BasicIStream),
    m_stream(stream) {}


template <typename Elem, typename Traits>
bool BasicIStreamCommandReader<Elem, Traits>::BasicIStreamCommandReader::read()
{
    std::getline(m_stream, m_data);
    m_timestamp = std::chrono::system_clock::now();

    return true;
}


template <typename Elem, typename Traits>
bool BasicIStreamCommandReader<Elem, Traits>::BasicIStreamCommandReader::endData()
{
    return m_stream.eof();
}
