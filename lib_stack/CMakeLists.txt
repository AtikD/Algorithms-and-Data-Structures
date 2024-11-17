add_library(TStack INTERFACE)

target_include_directories(TStack INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(TStack INTERFACE TMassive)