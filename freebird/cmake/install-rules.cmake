if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/freebird-${PROJECT_VERSION}"
      CACHE STRING ""
  )
  set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package freebird)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT freebird_Development
)

install(
    TARGETS freebird_freebird
    EXPORT freebirdTargets
    RUNTIME #
    COMPONENT freebird_Runtime
    LIBRARY #
    COMPONENT freebird_Runtime
    NAMELINK_COMPONENT freebird_Development
    ARCHIVE #
    COMPONENT freebird_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    freebird_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE freebird_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(freebird_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${freebird_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT freebird_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${freebird_INSTALL_CMAKEDIR}"
    COMPONENT freebird_Development
)

install(
    EXPORT freebirdTargets
    NAMESPACE freebird::
    DESTINATION "${freebird_INSTALL_CMAKEDIR}"
    COMPONENT freebird_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
