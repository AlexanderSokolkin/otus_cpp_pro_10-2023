set(HEADERS
        basic_ostream_block_writer.h
        block_writer_factory.h
        i_block_writer.h
        log_block_writer.h
        writer_type.h)

set(SOURCES
        i_block_writer.cpp
        log_block_writer.cpp)


target_include_directories(bulk
        PRIVATE ${CMAKE_SOURCE_DIR})

target_sources(bulk
        PRIVATE
            ${HEADERS}
            ${SOURCES})
