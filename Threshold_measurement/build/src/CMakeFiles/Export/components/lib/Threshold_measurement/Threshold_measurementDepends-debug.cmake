#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Threshold_measurement" for configuration "Debug"
set_property(TARGET Threshold_measurement APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Threshold_measurement PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/components/lib/Threshold_measurement.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "RTC112_vc12d;coil112_vc12d;omniORB421_rtd;omniDynamic421_rtd;omnithread40_rtd;advapi32;ws2_32;mswsock"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/components/bin/Threshold_measurement.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS Threshold_measurement )
list(APPEND _IMPORT_CHECK_FILES_FOR_Threshold_measurement "${_IMPORT_PREFIX}/components/lib/Threshold_measurement.lib" "${_IMPORT_PREFIX}/components/bin/Threshold_measurement.dll" )

# Import target "Threshold_measurementComp" for configuration "Debug"
set_property(TARGET Threshold_measurementComp APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Threshold_measurementComp PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/components/bin/Threshold_measurementComp.exe"
  )

list(APPEND _IMPORT_CHECK_TARGETS Threshold_measurementComp )
list(APPEND _IMPORT_CHECK_FILES_FOR_Threshold_measurementComp "${_IMPORT_PREFIX}/components/bin/Threshold_measurementComp.exe" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
