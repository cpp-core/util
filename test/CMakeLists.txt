cmake_minimum_required (VERSION 3.22 FATAL_ERROR)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)

find_package(googletest REQUIRED)
find_package(Threads REQUIRED)

set(TESTS
  util/argp/parse
  util/arith_star
  util/bool32
  util/guid
  util/has_common_element
  util/phantom
  util/range_for_enum
  util/range_for_pair
  util/range_for_reverse
  util/range_for_zip
  util/reinterpret_as
  util/round
  util/sbs
  util/scanner
  util/signum
  util/span
  util/splat
  util/tribool
  util/tribool32
  util/type_map
  util/unit_real
  util/unsigned_real
  util/view
  util/zorder
  )

set(LIBRARIES
  cxx_core_util
  cxx_coro_stream::cxx_coro_stream
  googletest::cxx-googletest
  Threads::Threads)
include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/configure_tests.cmake)
configure_tests("core" "${LIBRARIES}" ${TESTS})
