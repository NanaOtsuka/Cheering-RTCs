# Threshold_measurement CMake config file
#
# This file sets the following variables:
# Threshold_measurement_FOUND - Always TRUE.
# Threshold_measurement_INCLUDE_DIRS - Directories containing the Threshold_measurement include files.
# Threshold_measurement_IDL_DIRS - Directories containing the Threshold_measurement IDL files.
# Threshold_measurement_LIBRARIES - Libraries needed to use Threshold_measurement.
# Threshold_measurement_DEFINITIONS - Compiler flags for Threshold_measurement.
# Threshold_measurement_VERSION - The version of Threshold_measurement found.
# Threshold_measurement_VERSION_MAJOR - The major version of Threshold_measurement found.
# Threshold_measurement_VERSION_MINOR - The minor version of Threshold_measurement found.
# Threshold_measurement_VERSION_REVISION - The revision version of Threshold_measurement found.
# Threshold_measurement_VERSION_CANDIDATE - The candidate version of Threshold_measurement found.

message(STATUS "Found Threshold_measurement-1.0.0")
set(Threshold_measurement_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(Threshold_measurement_INCLUDE_DIRS
#    "C:/Program Files (x86)/Threshold_measurement/include/threshold_measurement-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(Threshold_measurement_IDL_DIRS
#    "C:/Program Files (x86)/Threshold_measurement/include/threshold_measurement-1/idl")
set(Threshold_measurement_INCLUDE_DIRS
    "C:/Program Files (x86)/Threshold_measurement/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(Threshold_measurement_IDL_DIRS
    "C:/Program Files (x86)/Threshold_measurement/include//idl")


if(WIN32)
    set(Threshold_measurement_LIBRARIES
        "C:/Program Files (x86)/Threshold_measurement/components/lib/threshold_measurement.lib"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(Threshold_measurement_LIBRARIES
        "C:/Program Files (x86)/Threshold_measurement/components/lib/threshold_measurement.dll"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(Threshold_measurement_DEFINITIONS ${<dependency>_DEFINITIONS})

set(Threshold_measurement_VERSION 1.0.0)
set(Threshold_measurement_VERSION_MAJOR 1)
set(Threshold_measurement_VERSION_MINOR 0)
set(Threshold_measurement_VERSION_REVISION 0)
set(Threshold_measurement_VERSION_CANDIDATE )

