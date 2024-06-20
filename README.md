# Timestamp Generator

Utility to generate a timestamp from current time

## Build instructions

On Linux platform open any terminal emulator.  
On Windows platform open Git Bash or equivalent LINUX/UNIX like terminal emulator.

Below are provided exmple instructions

```
PROJECT_DIR="$(pwd)"
echo $PROJECT_DIR
/c/git/timestamp_generator

cmake --build "${PROJECT_DIR}/cmake-build-release/" --target clean
cmake --build "${PROJECT_DIR}/cmake-build-debug/" --target clean
ls -l "${PROJECT_DIR}/cmake-build-release/Release/timestamp_generator.exe"
ls: cannot access '/c/git/timestamp_generator/cmake-build-release/Release/timestamp_generator.exe': No such file or directory
ls -l "${PROJECT_DIR}/cmake-build-release/Debug/timestamp_generator.exe"
ls: cannot access '/c/git/timestamp_generator/cmake-build-release/Debug/timestamp_generator.exe': No such file or directory

cmake -DCMAKE_BUILD_TYPE=Release -S "${PROJECT_DIR}" -B "${PROJECT_DIR}/cmake-build-release/"
-- Selecting Windows SDK version 10.0.22621.0 to target Windows 10.0.22631.
-- The C compiler identification is MSVC 19.40.33811.0
-- The CXX compiler identification is MSVC 19.40.33811.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.40.33807/bin/Hostx64/x64/cl.exe - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.40.33807/bin/Hostx64/x64/cl.exe - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (3.5s)
-- Generating done (0.0s)
-- Build files have been written to: C:/git/timestamp_generator/cmake-build-release

cmake -DCMAKE_BUILD_TYPE=Debug -S "${PROJECT_DIR}" -B "${PROJECT_DIR}/cmake-build-debug/"
-- Selecting Windows SDK version 10.0.22621.0 to target Windows 10.0.22631.
-- The C compiler identification is MSVC 19.40.33811.0
-- The CXX compiler identification is MSVC 19.40.33811.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.40.33807/bin/Hostx64/x64/cl.exe - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.40.33807/bin/Hostx64/x64/cl.exe - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (3.5s)
-- Generating done (0.0s)
-- Build files have been written to: C:/git/timestamp_generator/cmake-build-debug

PROJECT_NAME="${PROJECT_DIR##*/}"
echo ${PROJECT_NAME}
timestamp_generator
 
cmake --build "${PROJECT_DIR}/cmake-build-release" --target "${PROJECT_NAME}" --config Release
MSBuild version 17.10.4+10fbfbf2e for .NET Framework
 
  1>Checking Build System
  Building Custom Rule C:/git/timestamp_generator/CMakeLists.txt
  Scanning sources for module dependencies...
  IDGenerator.cpp
  main.cpp
  Compiling...
  main.cpp
  IDGenerator.cpp
  timestamp_generator.vcxproj -> C:\git\timestamp_generator\cmake-build-release\Release\timestamp_generator.exe
 
cmake --build "${PROJECT_DIR}/cmake-build-debug" --target "${PROJECT_NAME}" --config Debug
MSBuild version 17.10.4+10fbfbf2e for .NET Framework
 
  1>Checking Build System
  Building Custom Rule C:/git/timestamp_generator/CMakeLists.txt
  Scanning sources for module dependencies...
  IDGenerator.cpp
  main.cpp
  Compiling...
  main.cpp
  IDGenerator.cpp
  timestamp_generator.vcxproj -> C:\git\timestamp_generator\cmake-build-release\Debug\timestamp_generator.exe 
 
"${PROJECT_DIR}/cmake-build-release/Release/timestamp_generator.exe"
"${PROJECT_DIR}/cmake-build-release/Debug/timestamp_generator.exe"
```

## `man` page
```
NAME
timestamp_generator - generates timestamp from current time

SYNOPSIS
./timestamp_generator [-p | --precision <PRECISION>] [-d | --padding]

DESCRIPTION
timestamp_generator is an utility to generate a timestamp from current time in various precision and format. The generation is performed in a threa-safe manner.

OPTIONS
       -p, --precision
           Sets the precision of the timestamp. Can be one of: year, month, day, hour, minute, second, millisecond, microsecond, nanosecond.

       -d, --nopadding
           When present, this option disables padding the suffix after seconds with zeros '0' from left, when the value is less than three digits long, to maintain a fixed-length format.
```

Note: Options are not implemented yet.
