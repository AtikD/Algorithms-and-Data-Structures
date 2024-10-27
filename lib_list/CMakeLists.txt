add_library(TList STATIC node.cpp list.cpp)

target_include_directories(TList PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})