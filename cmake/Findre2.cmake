message(STATUS "Executing Findre2.cmake")

find_path(RE2_INCLUDE_DIR re2/re2.h
    HINTS
    /usr/include
    /usr/local/include
)
find_library(RE2_LIBRARY NAMES re2
    HINTS
    /usr/lib
    /usr/lib/x86_64-linux-gnu
    /usr/local/lib
)

message(STATUS "RE2_INCLUDE_DIR: ${RE2_INCLUDE_DIR}")
message(STATUS "RE2_LIBRARY: ${RE2_LIBRARY}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(re2 DEFAULT_MSG RE2_LIBRARY RE2_INCLUDE_DIR)

if(RE2_FOUND)
  set(RE2_LIBRARIES ${RE2_LIBRARY})
  set(RE2_INCLUDE_DIRS ${RE2_INCLUDE_DIR})
endif()

mark_as_advanced(RE2_INCLUDE_DIR RE2_LIBRARY)
