add_library(THash INTERFACE)

target_include_directories(THash INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(THash INTERFACE TMassive TPair)