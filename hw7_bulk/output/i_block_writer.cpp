#include "i_block_writer.h"


IBlockWriter::IBlockWriter(WriterType type) : m_type(type) {}

WriterType IBlockWriter::type() const
{
    return m_type;
}
