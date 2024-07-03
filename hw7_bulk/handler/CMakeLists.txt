set(HEADERS
        dynamic_handler.h
        handler_pool.h
        handler_type.h
        i_handler.h
        static_handler.h)

set(SOURCES
        dynamic_handler.cpp
        handler_pool.cpp
        i_handler.cpp
        static_handler.cpp)

target_include_directories(bulk
        PRIVATE ${CMAKE_SOURCE_DIR})


target_sources(bulk
        PRIVATE
            ${HEADERS}
            ${SOURCES})
