add_library(TQueue INTERFACE)

target_include_directories(TQueue INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(TStack INTERFACE TMassive)