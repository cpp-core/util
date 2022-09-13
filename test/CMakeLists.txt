cmake_minimum_required (VERSION 3.22 FATAL_ERROR)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)

find_package(googletest REQUIRED)
find_package(Threads REQUIRED)

set(TESTS
  util/arith_star
  util/bool32
  util/guid
  util/has_common_element
  util/phantom
  util/round
  util/signum
  util/span
  util/splat
  util/tribool
  util/tribool32
  util/type_map
  util/view
  )

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/configure_tests.cmake)
set(LIBS "cxx_core_util;googletest::cxx-googletest;Threads::Threads")
configure_tests("core" "${LIBS}" ${TESTS})
