set(PROJECT_NAME shunting_yard)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/shunting_yard.h
)

set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/tokenizer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/shunting_yard.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ${HEADERS})