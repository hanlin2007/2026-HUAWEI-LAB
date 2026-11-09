add_library(adas ExecutorImpl.cpp PoseHandler.cpp Point.cpp Direction.cpp)
target_include_directories(adas PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(adas PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic;-Wnon-virtual-dtor;-Woverloaded-virtual>)

add_executable(adas_demo ../example/adas_demo.cpp)
target_link_libraries(adas_demo PRIVATE adas)
