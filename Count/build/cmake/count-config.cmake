# Count CMake config file
#
# This file sets the following variables:
# Count_FOUND - Always TRUE.
# Count_INCLUDE_DIRS - Directories containing the Count include files.
# Count_IDL_DIRS - Directories containing the Count IDL files.
# Count_LIBRARIES - Libraries needed to use Count.
# Count_DEFINITIONS - Compiler flags for Count.
# Count_VERSION - The version of Count found.
# Count_VERSION_MAJOR - The major version of Count found.
# Count_VERSION_MINOR - The minor version of Count found.
# Count_VERSION_REVISION - The revision version of Count found.
# Count_VERSION_CANDIDATE - The candidate version of Count found.

message(STATUS "Found Count-1.0.0")
set(Count_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(Count_INCLUDE_DIRS
#    "C:/Program Files (x86)/Count/include/count-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(Count_IDL_DIRS
#    "C:/Program Files (x86)/Count/include/count-1/idl")
set(Count_INCLUDE_DIRS
    "C:/Program Files (x86)/Count/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(Count_IDL_DIRS
    "C:/Program Files (x86)/Count/include//idl")


if(WIN32)
    set(Count_LIBRARIES
        "C:/Program Files (x86)/Count/components/lib/count.lib"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(Count_LIBRARIES
        "C:/Program Files (x86)/Count/components/lib/count.dll"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(Count_DEFINITIONS ${<dependency>_DEFINITIONS})

set(Count_VERSION 1.0.0)
set(Count_VERSION_MAJOR 1)
set(Count_VERSION_MINOR 0)
set(Count_VERSION_REVISION 0)
set(Count_VERSION_CANDIDATE )

