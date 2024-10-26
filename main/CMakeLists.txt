add_executable(Application main.cpp)

target_link_libraries(Application PUBLIC EasyExample)

target_include_directories(Application PUBLIC ${PROJECT_SOURCE_DIR}/lib_easy_example)
