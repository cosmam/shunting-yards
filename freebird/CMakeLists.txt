cmake_minimum_required(VERSION 3.21)

include(cmake/prelude.cmake)

project(
    freebird
    VERSION 0.1.0
    DESCRIPTION "freebird description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES C
)

include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    freebird_freebird
    source/freebird.c
)
add_library(freebird::freebird ALIAS freebird_freebird)

include(GenerateExportHeader)
generate_export_header(
    freebird_freebird
    BASE_NAME freebird
    EXPORT_FILE_NAME export/freebird/freebird_export.h
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(freebird_freebird PUBLIC FREEBIRD_STATIC_DEFINE)
endif()

set_target_properties(
    freebird_freebird PROPERTIES
    C_VISIBILITY_PRESET hidden
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME freebird
    OUTPUT_NAME freebird
)

target_include_directories(
    freebird_freebird ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    freebird_freebird SYSTEM
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(freebird_freebird PUBLIC c_std_99)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Examples ----

if(PROJECT_IS_TOP_LEVEL)
  option(BUILD_EXAMPLES "Build examples tree." "${freebird_DEVELOPER_MODE}")
  if(BUILD_EXAMPLES)
    add_subdirectory(example)
  endif()
endif()

# ---- Developer mode ----

if(NOT freebird_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of freebird"
  )
endif()

include(cmake/dev-mode.cmake)
