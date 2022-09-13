cmake_minimum_required (VERSION 3.22 FATAL_ERROR)
project (cxx_core_util VERSION 0.1 LANGUAGES C CXX)

# Make including this file idempotent
#
if(TARGET cxx_core_util)
  return()
endif()

# Configuration variables.
#
# Build the tests and set directories if this is the master project
#
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(CORE_UTIL_TEST ON CACHE BOOL "Generate the tests.")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_DOCS_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/docs)
  
  # Have cmake output the compilation commands
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

# Options for generating tests and documentation.
#
option(CORE_UTIL_TEST "Generate the tests." OFF)
option(CORE_UTIL_DOCS "Generate the docs." OFF)

# Add our dependencies
#
include(GNUInstallDirs)
find_package(fmt)
find_package(nlohmann_json)

# Output configuration
#
message("-- cxx-core-util: Configuration: ${CMAKE_CURRENT_SOURCE_DIR}")
message("-- cxx-core-util: Included from: ${CMAKE_SOURCE_DIR}")
message("-- cxx-core-util: CORE_UTIL_TEST ${CORE_UTIL_TEST}")
message("-- cxx-core-util: CORE_UTIL_DOCS ${CORE_UTIL_DOCS}")
message("-- cxx-core-util: CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

# Compilation
#
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall)
add_compile_options(-stdlib=libc++)
add_compile_options(-O)
add_link_options(-stdlib=libc++)

set(SOURCES
  util/bool32
  util/guid
  util/random
  util/round
  util/tribool
  util/tribool32
  util/unit_real
  util/unsigned_real
  )

foreach(NAME ${SOURCES})
  list(APPEND FILES "src/core/${NAME}.cpp")
endforeach()

add_library(cxx_core_util ${FILES})

target_link_libraries(cxx_core_util PUBLIC fmt::fmt nlohmann_json::nlohmann_json)

target_include_directories(cxx_core_util
  PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Optionally configure the tests
#
if(CORE_UTIL_TEST)
  enable_testing()
  if (NOT TARGET check)
    add_custom_target(check ${CMAKE_CTEST_COMMAND})
    add_custom_target(check_detail ${CMAKE_CTEST_COMMAND} -V)
  endif()
  add_subdirectory(test)
endif()

# Optionally configure the documentation
#
# if(CORE_UTIL_DOCS)
#   add_subdirectory(docs)
# endif()

# Installation
#
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/install_config.cmake)
install_config(cxx_core_util)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/core/util DESTINATION include/core/)
