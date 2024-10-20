cmake_minimum_required(VERSION 3.24)

# Загрузка Google Test с использованием FetchContent
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
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
    test_massive.cpp
    test_stack.cpp
)

# Создаём (или обновляем) исполняемый файл с новыми тестами
add_executable(Tests ${TEST_SOURCES})

# Остальные настройки остаются прежними
target_link_libraries(Tests PRIVATE EasyExample gtest gtest_main)
target_include_directories(Tests PRIVATE ${PROJECT_SOURCE_DIR}/lib_easy_example)

# Регистрируем тесты
add_test(NAME EasyExampleTests COMMAND Tests)