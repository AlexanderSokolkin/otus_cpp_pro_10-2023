#pragma once
#include "i_command_reader.h"
#include <istream>


template <typename Elem, typename Traits>
class BasicIStreamCommandReader : public ICommandReader
{
public:
    BasicIStreamCommandReader(std::basic_istream<Elem, Traits>& stream);
    ~BasicIStreamCommandReader() override = default;

protected:
    bool read() override;
    bool endData() override;

private:
    std::basic_istream<Elem, Traits>& m_stream;
};


template <typename Elem, typename Traits>
BasicIStreamCommandReader(std::istream&) -> BasicIStreamCommandReader<std::istream::char_type, std::istream::traits_type>;


#include "basic_istream_command_reader.inl"
