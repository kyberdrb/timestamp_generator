cmake_minimum_required(VERSION 3.28) # for Visual Studio (e.g. to rebuild/regenerate CMake cache)
#cmake_minimum_required(VERSION 3.29) # for Git Bash - building from terminal, Linux etc.

project(timestamp_generator)

message("Project name: ${PROJECT_NAME}")

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

# MSVC
set(MSVC_VERSION_NUM)
if (MSVC)
    set(MSVC_VERSION ${CMAKE_CXX_COMPILER_VERSION})
    message(STATUS "MSVC version: ${MSVC_VERSION}")
    string(REPLACE "." "" MSVC_VERSION_NUM ${MSVC_VERSION}) # Convert MSVC version to a numeric value for comparison
    message(STATUS "MSVC version: ${MSVC_VERSION}")
    message(STATUS "MSVC version number: ${MSVC_VERSION_NUM}")
else()
    message(STATUS "GCC/Clang version: ${CMAKE_CXX_COMPILER_VERSION}")
endif()

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

if (NOT MSVC)
# Debug
target_compile_options(timestamp_generator PRIVATE
    -g
    #-ggdb
        -Wall
        -Wextra
        -Werror
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
endif()

if (MSVC)
    message(STATUS "Setting compiler options for MSVC")

    # Define Debug build options
    set(DEBUG_COMPILE_OPTIONS
            /Od
            /RTC1
            /Zi
            /Wall
            /W4
            /WX
            /fsanitize=address # AddressSanitizer - requires modifying the Visual Studio installer and installing module 'C++ AddressSanitizer' either from search bar in category 'Debugging and Testing' or in the tree view from 'Desktop development in C++ -> Optional -> C++ AddressSanitizer' 
    )
    set(DEBUG_LINK_OPTIONS
            /DEBUG # extended reporting for address sanitizer enabled by '/fsanitize=address'
            /INCREMENTAL:NO # set to 'NO' to resolve warning "LINK : warning LNK4300: ignoring '/INCREMENTAL' because input module contains ASAN metadata"
            /SUBSYSTEM:CONSOLE
    )

    # Define Release build options
    set(RELEASE_COMPILE_OPTIONS
            /O2
            /GL
    )
    set(RELEASE_LINK_OPTIONS
            /LTCG
            /INCREMENTAL:NO
            /OPT:REF
            /OPT:ICF
            #/DEBUG # Optional, for profiling tools
    )

    # Print the compiler options
    message(STATUS "Debug compiler options: ${DEBUG_COMPILE_OPTIONS}")
    message(STATUS "Release compiler options: ${RELEASE_COMPILE_OPTIONS}")

    # Print the linker options
    message(STATUS "Debug linker options: ${DEBUG_LINK_OPTIONS}")
    message(STATUS "Release linker options: ${RELEASE_LINK_OPTIONS}")

    # Apply the compile and link options
    target_compile_options(timestamp_generator PRIVATE
            "$<$<CONFIG:Debug>:${DEBUG_COMPILE_OPTIONS}>"
            "$<$<CONFIG:Release>:${RELEASE_COMPILE_OPTIONS}>"
    )

    target_link_options(timestamp_generator PRIVATE
            "$<$<CONFIG:Debug>:${DEBUG_LINK_OPTIONS}>"
            "$<$<CONFIG:Release>:${RELEASE_LINK_OPTIONS}>"
    )

    # Copy the ASan DLL for enhanced reporting for compiler option '/fsanitize=address' is copied to the output directory

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_custom_command(TARGET timestamp_generator POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.40.33807/bin/Hostx64/x64/clang_rt.asan_dbg_dynamic-x86_64.dll"
            "$<TARGET_FILE_DIR:timestamp_generator>")
    endif()

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_custom_command(TARGET timestamp_generator POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.40.33807/bin/Hostx64/x64/clang_rt.asan_dynamic-x86_64.dll"
            "$<TARGET_FILE_DIR:timestamp_generator>")
    endif()

#    add_custom_command(TARGET timestamp_generator POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.40.33807/bin/Hostx64/x64/clang_rt.asan_dbg_dynamic-x86_64.dll"
#            "$<$<CONFIG:Debug>:${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/>)")

#    add_custom_command(TARGET timestamp_generator POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.40.33807/bin/Hostx64/x64/clang_rt.asan_dbg_dynamic-x86_64.dll"
#            "$<$<CONFIG:Release>:${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/>)")

endif ()

get_target_property(COMPILE_OPTIONS timestamp_generator COMPILE_OPTIONS)
message(STATUS "Compile options for 'timestamp_generator': ${COMPILE_OPTIONS}")
