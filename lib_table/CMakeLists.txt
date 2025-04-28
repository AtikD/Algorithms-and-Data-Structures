add_library(ITable INTERFACE)

target_include_directories(ITable INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(TStack INTERFACE TList)