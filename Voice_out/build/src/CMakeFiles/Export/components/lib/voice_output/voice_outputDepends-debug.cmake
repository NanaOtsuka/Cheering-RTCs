#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "voice_output" for configuration "Debug"
set_property(TARGET voice_output APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(voice_output PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/components/lib/voice_output.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "RTC112_vc12d;coil112_vc12d;omniORB421_rtd;omniDynamic421_rtd;omnithread40_rtd;advapi32;ws2_32;mswsock"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/components/bin/voice_output.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS voice_output )
list(APPEND _IMPORT_CHECK_FILES_FOR_voice_output "${_IMPORT_PREFIX}/components/lib/voice_output.lib" "${_IMPORT_PREFIX}/components/bin/voice_output.dll" )

# Import target "voice_outputcomp" for configuration "Debug"
set_property(TARGET voice_outputcomp APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(voice_outputcomp PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/components/bin/voice_outputcomp.exe"
  )

list(APPEND _IMPORT_CHECK_TARGETS voice_outputcomp )
list(APPEND _IMPORT_CHECK_FILES_FOR_voice_outputcomp "${_IMPORT_PREFIX}/components/bin/voice_outputcomp.exe" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
