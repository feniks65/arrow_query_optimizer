message(STATUS "Executing FindLZ4.cmake")

find_path(LZ4_INCLUDE_DIR lz4.h
    HINTS
    /usr/include
    /usr/local/include
)
find_library(LZ4_LIBRARY NAMES lz4
    HINTS
    /usr/lib
    /usr/lib/x86_64-linux-gnu
    /usr/local/lib
)

message(STATUS "LZ4_INCLUDE_DIR: ${LZ4_INCLUDE_DIR}")
message(STATUS "LZ4_LIBRARY: ${LZ4_LIBRARY}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LZ4 DEFAULT_MSG LZ4_LIBRARY LZ4_INCLUDE_DIR)

if(LZ4_FOUND)
  set(LZ4_LIBRARIES ${LZ4_LIBRARY})
  set(LZ4_INCLUDE_DIRS ${LZ4_INCLUDE_DIR})
endif()

mark_as_advanced(LZ4_INCLUDE_DIR LZ4_LIBRARY)
