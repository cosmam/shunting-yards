enable_testing()

set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/shunting_yard-test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tokenizer-test.cpp
)

add_executable(shunting_yard_test main.cpp ${SOURCES})

target_link_libraries(
  shunting_yard
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)