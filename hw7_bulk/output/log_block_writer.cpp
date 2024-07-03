#include "log_block_writer.h"
#include "command.h"
#include <fstream>
#include <string>



LogBlockWriter::LogBlockWriter(const std::filesystem::path& path) : IBlockWriter(WriterType::Log), m_path(path) {}


bool LogBlockWriter::write(const CommandBlock& block)
{
    if (block.empty()) {
        return true;
    }

    // create filename
    auto timestamp = block.front().timestamp;
    auto time = std::chrono::duration_cast<std::chrono::seconds>(timestamp.time_since_epoch()).count();
    std::string fileName;
    fileName.reserve(20);
    fileName = "bulk";
    fileName += std::to_string(time);
    fileName += ".log";

    // create file
    std::filesystem::path filePath = m_path / fileName;
    std::ofstream f(filePath);
    if (!f.is_open()) {
        return false;
    }

    // write
    block.iter_resetCounter();
    while (block.iter_next()) {
        f << block.iter_command().name << " ";
    }
    f << std::endl;
    f.close();

    return true;
}
