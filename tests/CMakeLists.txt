set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
add_subdirectory(googletest EXCLUDE_FROM_ALL)

# 在这里添加自己的测试目标，并链接 gtest_main。
