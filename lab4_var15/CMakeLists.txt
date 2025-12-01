cmake_minimum_required(VERSION 3.16)
project(Lab04_Metaprogramming CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE TEST_FILES tests/*.cpp)

# ============================
#  GOOGLE TEST FIXED VERSION
# ============================

# First try system gtest
find_package(GTest)

if (NOT GTest_FOUND)
    message(WARNING "⚠️ System GTest not found — downloading...")

    include(FetchContent)

    # Required FIX for Windows + CMake >= 3.25
    set(FETCHCONTENT_QUIET OFF)
    set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
        GIT_SHALLOW FALSE     # <---- FIX #1
    )

    FetchContent_MakeAvailable(googletest)
    set(GTEST_LIBS GTest::gtest GTest::gtest_main)
else()
    message(STATUS "✅ Found system GoogleTest")
    include_directories(${GTEST_INCLUDE_DIRS})
    set(GTEST_LIBS ${GTEST_LIBRARIES})
endif()

# ============================

add_executable(run_tests ${SRC_FILES} ${TEST_FILES})
target_link_libraries(run_tests PRIVATE ${GTEST_LIBS} pthread)

enable_testing()
add_test(NAME Lab04Tests COMMAND run_tests)
