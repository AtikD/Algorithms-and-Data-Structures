add_library(TPolynom STATIC src/cmonom.cpp)

target_include_directories(TPolynom PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(TPolynom PRIVATE TList)