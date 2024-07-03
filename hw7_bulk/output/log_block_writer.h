#pragma once
#include "i_block_writer.h"
#include <filesystem>



class LogBlockWriter : public IBlockWriter
{
public:
    LogBlockWriter(const std::filesystem::path& path);
    ~LogBlockWriter() override = default;

    bool write(const CommandBlock& block) override;

private:
    std::filesystem::path m_path;
};
