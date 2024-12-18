add_library(TCalculator STATIC src/lexem.cpp)

target_include_directories(TCalculator PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(TCalculator PRIVATE TList TAlgorithms TStack)