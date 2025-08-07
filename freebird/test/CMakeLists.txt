cmake_minimum_required(VERSION 3.21)

project(freebirdTests LANGUAGES C)

include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(freebird REQUIRED)
  enable_testing()
endif()

# ---- Tests ----

add_executable(freebird_test source/freebird_test.c)
target_link_libraries(freebird_test PRIVATE freebird::freebird)
target_compile_features(freebird_test PRIVATE c_std_99)

add_test(NAME freebird_test COMMAND freebird_test)

# ---- End-of-file commands ----

add_folders(Test)
