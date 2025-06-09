set(PROJECT_NAME shunting_yard_test)

enable_testing()

add_executable(
    ${PROJECT_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/tokenizer-test.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    shunting_yard
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})