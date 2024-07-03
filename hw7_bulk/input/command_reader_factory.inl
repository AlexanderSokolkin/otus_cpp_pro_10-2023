// #include "command_reader_factory.h"
#include "basic_istream_command_reader.h"
#include <istream>



template <typename Elem, typename Traits>
std::unique_ptr<ICommandReader> CommandReaderFactory::createConsoleReader(std::basic_istream<Elem, Traits>& stream)
{
    return std::unique_ptr<ICommandReader>(new BasicIStreamCommandReader(stream));
}
