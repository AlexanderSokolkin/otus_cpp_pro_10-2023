set(HEADERS
        basic_istream_command_reader.h
        command_reader_factory.h
        i_command_reader.h
        input_data.h
        reader_type.h)

set(SOURCES
        i_command_reader.cpp)


target_include_directories(bulk
        PRIVATE ${CMAKE_SOURCE_DIR})

target_sources(bulk
        PRIVATE
            ${HEADERS}
            ${SOURCES})
