cmake_minimum_required(VERSION 3.10)
project(ArrowQueryOptimizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Arrow package
find_package(Arrow REQUIRED)

# Add main executable
add_executable(query_optimizer src/main.cpp)
target_link_libraries(query_optimizer PRIVATE Arrow::arrow_shared)

# Add include directory
target_include_directories(query_optimizer PRIVATE include)

# Add test executable
add_executable(tests test/test_main.cpp)
target_link_libraries(tests PRIVATE Arrow::arrow_shared)
