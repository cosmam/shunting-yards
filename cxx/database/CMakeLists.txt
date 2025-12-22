set(PROJECT_NAME database_project)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/code.h
)

set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/code.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ${HEADERS})
