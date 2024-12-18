cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# Загрузка Google Test с использованием FetchContent
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# Для предотвращения установки Google Test в систему
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF)
set(BUILD_GTEST ON)

FetchContent_MakeAvailable(googletest)

# Добавляем новый тестовый файл
set(TEST_SOURCES
    test_easy_example.cpp
    test_additional.cpp
    test_pair.cpp
    test_massive.cpp
    test_vector.cpp
    test_stack.cpp
    test_queue.cpp
    test_list.cpp
)

# Создаём (или обновляем) исполняемый файл с новыми тестами
add_executable(Tests ${TEST_SOURCES})

# Подключаем необходимые библиотеки
target_link_libraries(Tests PRIVATE EasyExample TPair TMassive TVector TStack TQueue TList gtest gtest_main)

# Регистрируем тесты
add_test(NAME EasyExampleTests COMMAND Tests)
