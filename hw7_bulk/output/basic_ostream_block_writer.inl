// #include "basic_ostream_block_writer.h"
#include "command.h"


template <typename Elem, typename Traits>
BasicOStreamBlockWriter<Elem, Traits>::BasicOStreamBlockWriter(std::basic_ostream<Elem, Traits>& stream) :
    IBlockWriter(WriterType::BasicOStream),
    m_stream(stream) {}


template <typename Elem, typename Traits>
bool BasicOStreamBlockWriter<Elem, Traits>::BasicOStreamBlockWriter::write(const CommandBlock& block)
{
    if (block.empty()) {
        return true;
    }

    block.iter_resetCounter();
    while (block.iter_next()) {
        m_stream << block.iter_command().name << " ";
    }

    m_stream << std::endl;

    return true;
}
