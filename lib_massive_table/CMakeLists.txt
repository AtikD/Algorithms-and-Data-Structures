add_library(IMTable INTERFACE)

target_include_directories(IMTable INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(IMTable INTERFACE TPair TMassive)