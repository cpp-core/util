cmake_minimum_required (VERSION 3.22 FATAL_ERROR)
project (util VERSION 0.1 LANGUAGES C CXX)

# Make including this file idempotent
#
if(TARGET util OR TARGET util::util)
  return()
endif()

# Configuration variables.
#
# Build the tests and set directories if this is the master project
#
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(UTIL_TEST ON CACHE BOOL "Generate the tests.")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_DOCS_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/docs)
  
  # Have cmake output the compilation commands and create a link to it
  # from the project root directory so the language server can find
  # it.
  #
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json)
endif()

# Options for generating tests and documentation.
#
option(UTIL_TEST "Generate the tests." OFF)
option(UTIL_DOCS "Generate the docs." OFF)

# Output configuration
#
message("-- util: Configuration: ${CMAKE_CURRENT_SOURCE_DIR}")
message("-- util: Included from: ${CMAKE_SOURCE_DIR}")
message("-- util: UTIL_TEST ${UTIL_TEST}")
message("-- util: UTIL_DOCS ${UTIL_DOCS}")
message("-- util: CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

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
include(cmake/cpp_core_find_package.cmake)
cpp_core_find_package(stream)
cpp_core_find_package(string)

set(JSON_Install ON CACHE INTERNAL "Have json create the install target")
cpp_core_find_package(nlohmann_json URL https://github.com/cpp-core/json VERSION v3.11.2)

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
  enable_testing()
  add_subdirectory(test)
endif()

# Optionally configure the documentation
#
# if(UTIL_DOCS)
#   add_subdirectory(docs)
# endif()

# Installation
#
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/install_config.cmake)
install_config(util)
