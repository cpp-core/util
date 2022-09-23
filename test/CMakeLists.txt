cmake_minimum_required (VERSION 3.22 FATAL_ERROR)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(TESTS
  util/argp/parse
  util/arith_star
  util/bool32
  util/cache
  util/guid
  util/hash/core
  util/hash/path
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
  util
  stream::stream
  GTest::gtest
  Threads::Threads)

function(maybe_include_test NEEDS ADDS DESCRIPTION ADD_TARGET)
  find_package(${NEEDS} QUIET)
  if(${${NEEDS}_FOUND})
    message("-- util: ${NEEDS} found, including ${DESCRIPTION} tests")
    foreach(ITEM ${ADDS})
      list(APPEND TESTS ${ITEM})
    endforeach()
    set(TESTS ${TESTS} PARENT_SCOPE)

    if(${ADD_TARGET})
      list(APPEND LIBRARIES ${NEEDS}::${NEEDS})
      set(LIBRARIES ${LIBRARIES} PARENT_SCOPE)
    endif()
  else()
    message("-- util: ${NEEDS} not found, excluding ${DESCRIPTION} tests")
  endif()
endfunction()

maybe_include_test(chrono util/hash/chrono "hash chrono" YES)
maybe_include_test(xtensor util/hash/xtensor "hash xtensor" NO)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/configure_tests.cmake)
configure_tests("core" "${LIBRARIES}" ${TESTS})
