cmake_minimum_required (VERSION 3.24 FATAL_ERROR)
project (util VERSION 0.1 LANGUAGES C CXX)

# Make including this file idempotent
#
if(TARGET util OR TARGET util::util)
  return()
endif()

# If this is the current project.
#
if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  # Laod the cmake recipes and utilities.
  #
  include(${CMAKE_CURRENT_LIST_DIR}/cmake/load_cmake_helpers.cmake)

  # Options for generating tests and documentation.
  #
  option(UTIL_TEST "Generate the tests." ON)
  option(UTIL_DOCS "Generate the docs." OFF)

  # compile_commands.json
  #
  symlink_compile_commands()

  # Convenience targets for git operations
  #
  make_submodule_pull_target()

else()
  option(UTIL_TEST "Generate the tests." OFF)
  option(UTIL_DOCS "Generate the docs." OFF)
endif()

# Put executables in the top-level binary directory
#
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Output configuration
#
message("-- util: Configuration: ${CMAKE_CURRENT_SOURCE_DIR}")
message("-- util: Included from: ${CMAKE_SOURCE_DIR}")
message("-- util: Install prefix: ${CMAKE_INSTALL_PREFIX}")
message("-- util: test ${UTIL_TEST}")
message("-- util: docs ${UTIL_DOCS}")

# Setup compilation before adding dependencies
#
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall)
add_compile_options(-stdlib=libc++)
add_compile_options(-O)
add_link_options(-stdlib=libc++)

# Add our dependencies
#
add_stream()
add_string()
add_json()

# Build the library
#
set(SOURCES
  util/argp/base
  util/argp/context
  util/argp/error
  util/bool32
  util/cache/cache
  util/guid
  util/hash/combine
  util/hash/path
  util/hash/detail/mixer
  util/random
  util/round
  util/scanner
  util/tribool
  util/tribool32
  util/unit_real
  util/unsigned_real
  util/zorder
  )

foreach(NAME ${SOURCES})
  list(APPEND FILES "src/core/${NAME}.cpp")
endforeach()

add_library(util ${FILES})
add_library(util::util ALIAS util)

# Define the header files for this library.
#
file(GLOB_RECURSE PUBLIC_INCLUDE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/*.h)
target_sources(util PUBLIC FILE_SET HEADERS BASE_DIRS include FILES ${PUBLIC_INCLUDE_FILES})

target_link_libraries(util PUBLIC stream::stream string::string nlohmann_json::nlohmann_json)

# Optionally configure the tests
#
if(UTIL_TEST)
  add_gtest()
  add_subdirectory(test)
endif()

# Optionally configure the documentation
#
# if(UTIL_DOCS)
#   add_subdirectory(docs)
# endif()

# Installation
#
install_config(util)
