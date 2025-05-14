cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(Algorithms-and-Data-Structures)
enable_testing()

# Опции для сборки с покрытием кода
option(CODE_COVERAGE "Enable coverage reporting" ON)

if(CODE_COVERAGE)
    # Проверка компилятора (на Windows обычно MSVC, но для покрытия нужен GCC или Clang)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        # Флаги для компиляции с покрытием кода
        set(COVERAGE_FLAGS "--coverage")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COVERAGE_FLAGS}")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COVERAGE_FLAGS}")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${COVERAGE_FLAGS}")
    else()
        message(WARNING "Покрытие кода поддерживается только с компиляторами GCC и Clang")
    endif()
endif()

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
add_subdirectory(lib_dsu)
add_subdirectory(lib_polynom)
add_subdirectory(lib_table)
add_subdirectory(lib_massive_table)
add_subdirectory(lib_bst)
add_subdirectory(lib_bst_table)
add_subdirectory(lib_heap)
add_subdirectory(lib_hash)
add_subdirectory(main)
add_subdirectory(tests)

