cmake_minimum_required(VERSION 3.10)
project(ArrowQueryOptimizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add cmake directory to module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Find required packages
find_package(Arrow REQUIRED)
find_package(LZ4 REQUIRED)
find_package(re2 REQUIRED)

# Add Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add main executable
add_executable(query_optimizer src/main.cpp)
target_link_libraries(query_optimizer PRIVATE 
    Arrow::arrow_shared
    ${LZ4_LIBRARIES}
    ${RE2_LIBRARIES}
)
target_include_directories(query_optimizer PRIVATE 
    include
    ${LZ4_INCLUDE_DIRS}
    ${RE2_INCLUDE_DIRS}
)

# Add test executable
add_executable(tests test/test_main.cpp test/sql_parser_test.cpp test/query_optimizer_test.cpp)
target_link_libraries(tests PRIVATE 
    Arrow::arrow_shared
    ${LZ4_LIBRARIES}
    ${RE2_LIBRARIES}
    gtest_main
)
target_include_directories(tests PRIVATE 
    include
    ${LZ4_INCLUDE_DIRS}
    ${RE2_INCLUDE_DIRS}
)

include(GoogleTest)
gtest_discover_tests(tests)

# Print status messages
message(STATUS "Arrow version: ${ARROW_VERSION}")
message(STATUS "LZ4 libraries: ${LZ4_LIBRARIES}")
message(STATUS "LZ4 include dirs: ${LZ4_INCLUDE_DIRS}")
message(STATUS "RE2 libraries: ${RE2_LIBRARIES}")
message(STATUS "RE2 include dirs: ${RE2_INCLUDE_DIRS}")
