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

# Создаём исполняемый файл тестов
add_executable(Tests test_easy_example.cpp)

# Линкуем с библиотекой и Google Test
target_link_libraries(Tests PRIVATE EasyExample gtest gtest_main)

# Указываем путь к заголовочным файлам библиотеки
target_include_directories(Tests PRIVATE ${PROJECT_SOURCE_DIR}/lib_easy_example)

# Регистрируем тесты
add_test(NAME EasyExampleTests COMMAND Tests)
