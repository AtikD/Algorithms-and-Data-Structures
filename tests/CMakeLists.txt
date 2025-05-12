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

file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Создаём (или обновляем) исполняемый файл с новыми тестами
# add_executable(Tests ${TEST_SOURCES})
add_executable(Tests test_bst_table.cpp)

# Подключаем необходимые библиотеки
target_link_libraries(Tests PRIVATE EasyExample TBSTTable TBST IMTable ITable TPair TMassive TVector TPolynom TStack DSU TCalculator TQueue TAlgorithms TList TMatrix gtest gtest_main)

# Регистрируем тесты
add_test(NAME EasyExampleTests COMMAND Tests)
