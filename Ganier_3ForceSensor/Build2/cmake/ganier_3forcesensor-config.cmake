# Ganier_3ForceSensor CMake config file
#
# This file sets the following variables:
# Ganier_3ForceSensor_FOUND - Always TRUE.
# Ganier_3ForceSensor_INCLUDE_DIRS - Directories containing the Ganier_3ForceSensor include files.
# Ganier_3ForceSensor_IDL_DIRS - Directories containing the Ganier_3ForceSensor IDL files.
# Ganier_3ForceSensor_LIBRARIES - Libraries needed to use Ganier_3ForceSensor.
# Ganier_3ForceSensor_DEFINITIONS - Compiler flags for Ganier_3ForceSensor.
# Ganier_3ForceSensor_VERSION - The version of Ganier_3ForceSensor found.
# Ganier_3ForceSensor_VERSION_MAJOR - The major version of Ganier_3ForceSensor found.
# Ganier_3ForceSensor_VERSION_MINOR - The minor version of Ganier_3ForceSensor found.
# Ganier_3ForceSensor_VERSION_REVISION - The revision version of Ganier_3ForceSensor found.
# Ganier_3ForceSensor_VERSION_CANDIDATE - The candidate version of Ganier_3ForceSensor found.

message(STATUS "Found Ganier_3ForceSensor-1.0.0")
set(Ganier_3ForceSensor_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(Ganier_3ForceSensor_INCLUDE_DIRS
#    "C:/Program Files (x86)/Ganier_3ForceSensor/include/ganier_3forcesensor-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(Ganier_3ForceSensor_IDL_DIRS
#    "C:/Program Files (x86)/Ganier_3ForceSensor/include/ganier_3forcesensor-1/idl")
set(Ganier_3ForceSensor_INCLUDE_DIRS
    "C:/Program Files (x86)/Ganier_3ForceSensor/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(Ganier_3ForceSensor_IDL_DIRS
    "C:/Program Files (x86)/Ganier_3ForceSensor/include//idl")


if(WIN32)
    set(Ganier_3ForceSensor_LIBRARIES
        "C:/Program Files (x86)/Ganier_3ForceSensor/components/lib/ganier_3forcesensor.lib"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(Ganier_3ForceSensor_LIBRARIES
        "C:/Program Files (x86)/Ganier_3ForceSensor/components/lib/ganier_3forcesensor.dll"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(Ganier_3ForceSensor_DEFINITIONS ${<dependency>_DEFINITIONS})

set(Ganier_3ForceSensor_VERSION 1.0.0)
set(Ganier_3ForceSensor_VERSION_MAJOR 1)
set(Ganier_3ForceSensor_VERSION_MINOR 0)
set(Ganier_3ForceSensor_VERSION_REVISION 0)
set(Ganier_3ForceSensor_VERSION_CANDIDATE )

