add_library(TMatrix INTERFACE)

target_include_directories(TMatrix INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(TMatrix INTERFACE TVector)