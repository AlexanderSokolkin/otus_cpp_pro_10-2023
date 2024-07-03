#pragma once
#include "writer_type.h"


class CommandBlock;


class IBlockWriter
{
public:
    IBlockWriter(WriterType type);
    virtual ~IBlockWriter() = default;

    WriterType type() const;

public:
    virtual bool write(const CommandBlock& block) = 0;

protected:
    WriterType m_type;
};
