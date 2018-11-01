#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "voice_output" for configuration "Release"
set_property(TARGET voice_output APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(voice_output PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/components/lib/voice_output.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "RTC112_vc12;coil112_vc12;omniORB421_rt;omniDynamic421_rt;omnithread40_rt;advapi32;ws2_32;mswsock"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/components/bin/voice_output.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS voice_output )
list(APPEND _IMPORT_CHECK_FILES_FOR_voice_output "${_IMPORT_PREFIX}/components/lib/voice_output.lib" "${_IMPORT_PREFIX}/components/bin/voice_output.dll" )

# Import target "voice_outputcomp" for configuration "Release"
set_property(TARGET voice_outputcomp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(voice_outputcomp PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/components/bin/voice_outputcomp.exe"
  )

list(APPEND _IMPORT_CHECK_TARGETS voice_outputcomp )
list(APPEND _IMPORT_CHECK_FILES_FOR_voice_outputcomp "${_IMPORT_PREFIX}/components/bin/voice_outputcomp.exe" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
