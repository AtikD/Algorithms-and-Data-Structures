cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(Algorithms-and-Data-Structures)

# Включаем поддержку тестирования
enable_testing()

# Добавляем подкаталоги
add_subdirectory(lib_easy_example)
add_subdirectory(lib_massive)
add_subdirectory(lib_vector)
add_subdirectory(main)
add_subdirectory(tests)