cmake_minimum_required (VERSION 3.22 FATAL_ERROR)
project (util VERSION 0.1 LANGUAGES C CXX)

# Make including this file idempotent
#
if(TARGET util)
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
  
  # Have cmake output the compilation commands
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

# Options for generating tests and documentation.
#
option(UTIL_TEST "Generate the tests." OFF)
option(UTIL_DOCS "Generate the docs." OFF)

# Add our dependencies
#
include(GNUInstallDirs)
find_package(string REQUIRED)
find_package(stream REQUIRED)
find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)

# Output configuration
#
message("-- util: Configuration: ${CMAKE_CURRENT_SOURCE_DIR}")
message("-- util: Included from: ${CMAKE_SOURCE_DIR}")
message("-- util: UTIL_TEST ${UTIL_TEST}")
message("-- util: UTIL_DOCS ${UTIL_DOCS}")
message("-- util: CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

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

target_link_libraries(util PUBLIC
  string::string
  stream::stream
  fmt::fmt
  nlohmann_json::nlohmann_json)

target_include_directories(util
  PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Optionally configure the tests
#
if(UTIL_TEST)
  enable_testing()
  if (NOT TARGET check)
    add_custom_target(check ${CMAKE_CTEST_COMMAND})
    add_custom_target(check_detail ${CMAKE_CTEST_COMMAND} -V)
  endif()
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
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/core/util DESTINATION include/core)
