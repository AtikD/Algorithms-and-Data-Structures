cmake_minimum_required(VERSION 3.15)

add_library(TBSTTable INTERFACE)

target_include_directories(TBSTTable INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(TBSTTable INTERFACE ITable TPair TBST)