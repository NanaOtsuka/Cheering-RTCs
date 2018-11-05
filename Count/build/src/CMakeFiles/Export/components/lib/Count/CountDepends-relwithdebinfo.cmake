#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Count" for configuration "RelWithDebInfo"
set_property(TARGET Count APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(Count PROPERTIES
  IMPORTED_IMPLIB_RELWITHDEBINFO "${_IMPORT_PREFIX}/components/lib/Count.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELWITHDEBINFO "RTC112_vc12;coil112_vc12;omniORB421_rt;omniDynamic421_rt;omnithread40_rt;advapi32;ws2_32;mswsock"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/components/bin/Count.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS Count )
list(APPEND _IMPORT_CHECK_FILES_FOR_Count "${_IMPORT_PREFIX}/components/lib/Count.lib" "${_IMPORT_PREFIX}/components/bin/Count.dll" )

# Import target "CountComp" for configuration "RelWithDebInfo"
set_property(TARGET CountComp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(CountComp PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/components/bin/CountComp.exe"
  )

list(APPEND _IMPORT_CHECK_TARGETS CountComp )
list(APPEND _IMPORT_CHECK_FILES_FOR_CountComp "${_IMPORT_PREFIX}/components/bin/CountComp.exe" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
