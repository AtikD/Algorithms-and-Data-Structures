add_executable(Application main.cpp)

target_link_libraries(Application PRIVATE 
    EasyExample TPair TMassive TVector TStack TQueue
)

target_compile_definitions(Application PRIVATE VECTOR)
