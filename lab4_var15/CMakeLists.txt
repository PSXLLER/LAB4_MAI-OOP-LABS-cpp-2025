cmake_minimum_required(VERSION 3.16)
project(Lab04_Metaprogramming CXX)

# --- Стандарт C++ ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Пути к заголовочным файлам ---
include_directories(include)

# --- Источники проекта ---
file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE TEST_FILES tests/*.cpp)

# =====================================================
# ============  УМНОЕ ПОДКЛЮЧЕНИЕ GOOGLE TEST =========
# =====================================================

find_package(GTest)

if (GTest_FOUND)
    message(STATUS "✅ Found system GoogleTest")
    include_directories(${GTEST_INCLUDE_DIRS})
    set(GTEST_LIBS ${GTEST_LIBRARIES})
else()
    message(WARNING "⚠️ System GTest not found — downloading automatically...")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
    )
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    set(GTEST_LIBS GTest::gtest GTest::gtest_main)
endif()

# =====================================================

# --- Исполняемый файл для тестов ---
add_executable(run_tests ${SRC_FILES} ${TEST_FILES})

# --- Линковка с GoogleTest и потоками ---
target_link_libraries(run_tests PRIVATE ${GTEST_LIBS} pthread)

# --- Включаем поддержку тестирования ---
enable_testing()
add_test(NAME Lab04Tests COMMAND run_tests)
