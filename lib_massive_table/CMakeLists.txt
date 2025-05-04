add_library(TMassiveTable INTERFACE)

target_include_directories(TMassiveTable INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(TMassiveTable INTERFACE TPair TMassive)