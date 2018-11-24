#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ganier_3forcesensor" for configuration "Debug"
set_property(TARGET ganier_3forcesensor APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(ganier_3forcesensor PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/components/lib/ganier_3forcesensor.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "RTC112_vc12d;coil112_vc12d;omniORB421_rtd;omniDynamic421_rtd;omnithread40_rtd;advapi32;ws2_32;mswsock"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/components/bin/ganier_3forcesensor.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS ganier_3forcesensor )
list(APPEND _IMPORT_CHECK_FILES_FOR_ganier_3forcesensor "${_IMPORT_PREFIX}/components/lib/ganier_3forcesensor.lib" "${_IMPORT_PREFIX}/components/bin/ganier_3forcesensor.dll" )

# Import target "ganier_3forcesensorcomp" for configuration "Debug"
set_property(TARGET ganier_3forcesensorcomp APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(ganier_3forcesensorcomp PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/components/bin/ganier_3forcesensorcomp.exe"
  )

list(APPEND _IMPORT_CHECK_TARGETS ganier_3forcesensorcomp )
list(APPEND _IMPORT_CHECK_FILES_FOR_ganier_3forcesensorcomp "${_IMPORT_PREFIX}/components/bin/ganier_3forcesensorcomp.exe" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
