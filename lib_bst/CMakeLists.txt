cmake_minimum_required(VERSION 3.15)

add_library(TBST INTERFACE)

target_include_directories(TBST INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(TBST INTERFACE ITable TQueue TStack)