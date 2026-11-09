set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
add_subdirectory(googletest EXCLUDE_FROM_ALL)

add_executable(adas_tests
    ExecutorTest.cpp
    ExecutorFastTest.cpp
    ExecutorFastRegressionTest.cpp
    StateTypesTest.cpp
    PoseEq.cpp
)
target_link_libraries(adas_tests PRIVATE adas gtest_main)

include(GoogleTest)
gtest_discover_tests(adas_tests)
