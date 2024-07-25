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

add_executable(timestamp_generator main.cpp
        Timestamp.cpp
        Timestamp.h
        Options.cpp
        Options.h
        OptionParserCrossPlatformStdOnly.cpp
        OptionParserCrossPlatformStdOnly.h
        OptionParserPosixOnlyViaGetopt.cpp
        OptionParserPosixOnlyViaGetopt.h
        CommandLineArgumentsOptionsParser.h)

# Conditionally add _DEBUG definition for Debug builds
target_compile_definitions(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:_DEBUG>
)

# Optionally, you can also define NDEBUG for Release builds
target_compile_definitions(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:NDEBUG>
)
