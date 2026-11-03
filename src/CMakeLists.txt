add_library(adas ExecutorImpl.cpp)
target_include_directories(adas PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(adas PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic;-Wnon-virtual-dtor;-Woverloaded-virtual>)
