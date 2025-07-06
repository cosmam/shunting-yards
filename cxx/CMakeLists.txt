cmake_minimum_required(VERSION 3.28)                                                # setting this is required
project(shunting_yard VERSION 0.1 DESCRIPTION "C++ shunting yard implementation")   # this sets the project name

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

set(CMAKE_BUILD_TYPE "Debug")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(CodeCoverage.cmake)
append_coverage_compiler_flags()

add_subdirectory(src)
add_subdirectory(tests)