cmake_minimum_required(VERSION 3.29)
project(timestamp_generator)

message("Project name: ${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 23)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
#    -ggdb \
#    -Wall -Werror -Wextra -Wpedantic \
#    -Wunused-parameter -Weffc++ -Wsign-conversion -Wconversion -Wmissing-declarations \
#    -fstrict-aliasing -Wstrict-aliasing \
#    -fprofile-arcs -ftest-coverage \
#    -fwrapv")
#
#message(STATUS "CXXFLAGS: ${CMAKE_CXX_FLAGS}")

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
    message(STATUS "POSIX-conforming compiler detected: Including files for class 'OptionParserPosixOnlyViaGetopt' into the build")
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

target_compile_options(timestamp_generator PRIVATE
        -ggdb
        -Wall
        -Wextra
        #-Werror
        -Wpedantic
        -Wunused-parameter
        -Weffc++
        -Wsign-conversion
        -Wconversion
        -Wmissing-declarations
        -fstrict-aliasing
        -Wstrict-aliasing
        #-fprofile-arcs
        #-ftest-coverage
        -fwrapv)

if(MSVC)
    message(STATUS "Setting compiler options for MSVC")
    target_compile_options(MyProject PRIVATE
            /W4            # Highest warning level
            #/WX            # Treat warnings as errors
            /RTC1          # Runtime error checks
            /sdl           # Security development lifecycle checks
            /Zi            # Debug information
            /fsanitize=address   # AddressSanitizer

            # if MSVC version >= 16.7 append undefined behavior sanitizer option to the compiler options list
            #/fsanitize=undefined # UndefinedBehaviorSanitizer
    )
endif ()

get_target_property(COMPILE_OPTIONS timestamp_generator COMPILE_OPTIONS)
message(STATUS "Compile options for 'timestamp_generator': ${COMPILE_OPTIONS}")
