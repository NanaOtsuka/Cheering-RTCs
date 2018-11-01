# Voice_output CMake config file
#
# This file sets the following variables:
# Voice_output_FOUND - Always TRUE.
# Voice_output_INCLUDE_DIRS - Directories containing the Voice_output include files.
# Voice_output_IDL_DIRS - Directories containing the Voice_output IDL files.
# Voice_output_LIBRARIES - Libraries needed to use Voice_output.
# Voice_output_DEFINITIONS - Compiler flags for Voice_output.
# Voice_output_VERSION - The version of Voice_output found.
# Voice_output_VERSION_MAJOR - The major version of Voice_output found.
# Voice_output_VERSION_MINOR - The minor version of Voice_output found.
# Voice_output_VERSION_REVISION - The revision version of Voice_output found.
# Voice_output_VERSION_CANDIDATE - The candidate version of Voice_output found.

message(STATUS "Found Voice_output-1.0.0")
set(Voice_output_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(Voice_output_INCLUDE_DIRS
#    "C:/Program Files (x86)/Voice_output/include/voice_output-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(Voice_output_IDL_DIRS
#    "C:/Program Files (x86)/Voice_output/include/voice_output-1/idl")
set(Voice_output_INCLUDE_DIRS
    "C:/Program Files (x86)/Voice_output/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(Voice_output_IDL_DIRS
    "C:/Program Files (x86)/Voice_output/include//idl")


if(WIN32)
    set(Voice_output_LIBRARIES
        "C:/Program Files (x86)/Voice_output/components/lib/voice_output.lib"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(Voice_output_LIBRARIES
        "C:/Program Files (x86)/Voice_output/components/lib/voice_output.dll"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(Voice_output_DEFINITIONS ${<dependency>_DEFINITIONS})

set(Voice_output_VERSION 1.0.0)
set(Voice_output_VERSION_MAJOR 1)
set(Voice_output_VERSION_MINOR 0)
set(Voice_output_VERSION_REVISION 0)
set(Voice_output_VERSION_CANDIDATE )

