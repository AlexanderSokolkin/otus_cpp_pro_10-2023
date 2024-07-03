#pragma once
#include <memory>


class IBlockWriter;
namespace std {
    template <typename Elem, typename Traits>
    class basic_ostream;
    namespace filesystem {
        class path;
    }
}


class BlockWriterFactory
{
public:
    template <typename Elem, typename Traits>
    static std::unique_ptr<IBlockWriter> createBasicOStreamWriter(std::basic_ostream<Elem, Traits>& stream);

    static std::unique_ptr<IBlockWriter> createLogWriter(const std::filesystem::path& path);
};

#include "block_writer_factory.inl"
