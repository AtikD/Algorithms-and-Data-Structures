add_executable(Application main.cpp)

target_link_libraries(Application PUBLIC EasyExample)
target_link_libraries(Application PUBLIC TMassive)
target_link_libraries(Application PUBLIC TPair)
target_link_libraries(Application PUBLIC TList)

target_include_directories(Application PUBLIC ${PROJECT_SOURCE_DIR}/lib_easy_example)
