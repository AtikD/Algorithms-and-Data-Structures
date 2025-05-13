add_library(THeap INTERFACE)

target_include_directories(THeap INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(THeap INTERFACE TMassive)