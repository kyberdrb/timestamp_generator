cmake_minimum_required(VERSION 3.29)
project(timestamp_generator)

set(CMAKE_CXX_STANDARD 23)

# Ensure CMake has a default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Print the build type: helps to verify
#  if the generated CMake compilation configuration
#  is matching the CMake build files for desired configuration
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

message(STATUS "Compiler type: ${CMAKE_CXX_COMPILER_ID}")

# List common source files
set(SOURCES
        Timestamp.cpp
        Options.cpp
        OptionParserCrossPlatformStdOnly.cpp
)

# List common header files
set(HEADERS
        Timestamp.h
        Options.h
        OptionParserCrossPlatformStdOnly.h
        CommandLineArgumentsOptionsParser.h
)

# Conditionally add source and header files for non-MSVC compilers
if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "Skipping inclusion of 'OptionParserPosixOnlyViaGetopt' class - compatible with POSIX-conforming compilers only")
    list(APPEND SOURCES OptionParserPosixOnlyViaGetopt.cpp)
    list(APPEND HEADERS OptionParserPosixOnlyViaGetopt.h)
endif()

add_executable(timestamp_generator main.cpp ${SOURCES} ${HEADERS})

# Conditionally add _DEBUG definition for Debug builds
target_compile_definitions(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:_DEBUG>
)

# Optionally, you can also define NDEBUG for Release builds
target_compile_definitions(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:NDEBUG>
)
