add_executable(Application main.cpp)

target_link_libraries(Application PRIVATE EasyExample TPair TMassive TQueue)

target_compile_definitions(Application PRIVATE QUEUE)