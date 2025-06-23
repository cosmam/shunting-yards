set(PROJECT_NAME equation_evaluator_test)

enable_testing()

add_executable(
    ${PROJECT_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/token-test.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    equation_evaluator
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME} PROPERTIES TEST_DISCOVERY_TIMEOUT 600)