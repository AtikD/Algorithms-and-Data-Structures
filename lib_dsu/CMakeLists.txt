add_library(DSU STATIC src/dsu.cpp)

target_include_directories(DSU PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
