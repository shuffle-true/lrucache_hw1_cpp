add_subdirectory(${LC_ROOT}/cmake/external/googletest EXCLUDE_FROM_ALL)

enable_testing()

set(LC_TEST_ROOT ${LC_ROOT}/test)

macro(AddTest TARGET SOURCES)
    add_executable(${TARGET} ${SOURCES})
    target_link_libraries(${TARGET} GTest::gtest_main)
    add_test(${TARGET} ${TARGET})
endmacro()

AddTest(
        common_test
        ${LC_TEST_ROOT}/unit/common_test.cc
)