# Enable vcpkg toolchain
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{CMAKE_TOOLCHAIN_FILE}"
        CACHE STRING "Vcpkg toolchain file")
  else()
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
  endif()
endif()

cmake_minimum_required(VERSION 3.15)
project(unix-shell CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h)
# Remove test files from main source list
list(FILTER SOURCE_FILES EXCLUDE REGEX ".*_test.cpp$")


# Main shell executable
add_executable(shell ${SOURCE_FILES})
# Link readline library

# GoogleTest setup
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)
enable_testing()

# Test sources (only *_test.cpp in tests/)
file(GLOB TEST_SOURCES tests/*_test.cpp)

# Test executable and linking
# Gather all source files except main.cpp for tests
file(GLOB_RECURSE NON_MAIN_SOURCES src/*.cpp)
list(FILTER NON_MAIN_SOURCES EXCLUDE REGEX ".*/main.cpp$")

add_executable(shell_tests ${TEST_SOURCES} ${NON_MAIN_SOURCES})
target_include_directories(shell_tests PRIVATE src)
find_package(PkgConfig REQUIRED)
pkg_check_modules(readline REQUIRED IMPORTED_TARGET readline)

target_link_libraries(shell PRIVATE PkgConfig::readline)
target_link_libraries(shell_tests PRIVATE gtest_main PkgConfig::readline)

include(GoogleTest)
gtest_discover_tests(shell_tests)

# Add integration tests subdirectory
add_subdirectory(tests/integration)

