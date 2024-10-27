add_executable(Application main.cpp)

target_link_libraries(Application PRIVATE EasyExample TPair TMassive TList)

target_compile_definitions(Application PRIVATE LIST)