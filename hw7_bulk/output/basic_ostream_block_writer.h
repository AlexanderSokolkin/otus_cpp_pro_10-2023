#pragma once
#include "i_block_writer.h"
#include <ostream>


template <typename Elem, typename Traits>
class BasicOStreamBlockWriter : public IBlockWriter
{
public:
    BasicOStreamBlockWriter(std::basic_ostream<Elem, Traits>& stream);
    ~BasicOStreamBlockWriter() override = default;

public:
    bool write(const CommandBlock& block) override;

private:
    std::basic_ostream<Elem, Traits>& m_stream;
};


template <typename Elem, typename Traits>
BasicOStreamBlockWriter(std::ostream&) -> BasicOStreamBlockWriter<std::ostream::char_type, std::ostream::traits_type>;

#include "basic_ostream_block_writer.inl"
