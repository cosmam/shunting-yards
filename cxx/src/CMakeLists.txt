set(PROJECT_NAME equation_evaluator)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/equation_evaluator.h
)

set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/token.cpp
    ${CMAKE_CURRENT_LIST_DIR}/equation_evaluator.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ${HEADERS})