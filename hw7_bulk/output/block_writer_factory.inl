#include "block_writer_factory.h"
#include "basic_ostream_block_writer.h"
#include "log_block_writer.h"
#include <ostream>
#include <filesystem>



template <typename Elem, typename Traits>
std::unique_ptr<IBlockWriter> BlockWriterFactory::createBasicOStreamWriter(std::basic_ostream<Elem, Traits>& stream)
{
    return std::unique_ptr<IBlockWriter>(new BasicOStreamBlockWriter(stream));
}

std::unique_ptr<IBlockWriter> BlockWriterFactory::createLogWriter(const std::filesystem::path& path)
{
    return std::unique_ptr<IBlockWriter>(new LogBlockWriter(path));
}
