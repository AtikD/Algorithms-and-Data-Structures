add_library(TAlgorithms STATIC source/parser.cpp)

target_include_directories(TAlgorithms PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(TAlgorithms PRIVATE TStack TList)