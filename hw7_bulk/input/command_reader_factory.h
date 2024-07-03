#pragma once
#include <memory>



class ICommandReader;
namespace std {
template <typename Elem, typename Traits>
class basic_istream;
}


class CommandReaderFactory
{
public:
    template <typename Elem, typename Traits>
    static std::unique_ptr<ICommandReader> createConsoleReader(std::basic_istream<Elem, Traits>& stream);
};

#include "command_reader_factory.inl"
