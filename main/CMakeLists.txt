add_executable(Application main.cpp)

target_link_libraries(Application PRIVATE EasyExample)

target_include_directories(Application PRIVATE ${PROJECT_SOURCE_DIR}/lib_easy_example)
