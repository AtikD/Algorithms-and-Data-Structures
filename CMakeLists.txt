cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(Algorithms-and-Data-Structures)

# Включаем поддержку тестирования
enable_testing()

# Добавляем подкаталоги
add_subdirectory(lib_easy_example)
add_subdirectory(lib_massive)
add_subdirectory(lib_vector)
add_subdirectory(lib_pair)
add_subdirectory(lib_stack)
add_subdirectory(lib_queue)
add_subdirectory(lib_list)
add_subdirectory(lib_algorithms)
add_subdirectory(lib_matrix)
add_subdirectory(lib_calculator)
add_subdirectory(main)
add_subdirectory(tests)