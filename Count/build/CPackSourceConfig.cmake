# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BINARY_7Z "OFF")
set(CPACK_BINARY_BUNDLE "")
set(CPACK_BINARY_CYGWIN "")
set(CPACK_BINARY_DEB "")
set(CPACK_BINARY_DRAGNDROP "")
set(CPACK_BINARY_FREEBSD "")
set(CPACK_BINARY_IFW "OFF")
set(CPACK_BINARY_NSIS "ON")
set(CPACK_BINARY_NUGET "OFF")
set(CPACK_BINARY_OSXX11 "")
set(CPACK_BINARY_PACKAGEMAKER "")
set(CPACK_BINARY_PRODUCTBUILD "")
set(CPACK_BINARY_RPM "")
set(CPACK_BINARY_STGZ "")
set(CPACK_BINARY_TBZ2 "")
set(CPACK_BINARY_TGZ "")
set(CPACK_BINARY_TXZ "")
set(CPACK_BINARY_TZ "")
set(CPACK_BINARY_WIX "OFF")
set(CPACK_BINARY_ZIP "OFF")
set(CPACK_BUILD_SOURCE_DIRS "C:/workspace/Count;C:/workspace/Count/build")
set(CPACK_CMAKE_GENERATOR "Visual Studio 12 2013")
set(CPACK_COMPONENTS_ALL "component;documentation")
set(CPACK_COMPONENTS_ALL_SET_BY_USER "TRUE")
set(CPACK_COMPONENT_COMPONENT_DESCRIPTION "Component library and stand-alone executable")
set(CPACK_COMPONENT_COMPONENT_DISPLAY_NAME "Applications")
set(CPACK_COMPONENT_DOCUMENTATION_DEPENDS "component")
set(CPACK_COMPONENT_DOCUMENTATION_DESCRIPTION "Component documentation")
set(CPACK_COMPONENT_DOCUMENTATION_DISPLAY_NAME "Documentation")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_GENERATOR "7Z;ZIP")
set(CPACK_IGNORE_FILES "/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.swp\$;\\.#;/#")
set(CPACK_INSTALLED_DIRECTORIES "C:/workspace/Count;/")
set(CPACK_INSTALL_CMAKE_PROJECTS "")
set(CPACK_INSTALL_PREFIX "C:/Program Files (x86)/Count")
set(CPACK_MODULE_PATH "")
set(CPACK_NSIS_DISPLAY_NAME "Count100")
set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "  Rename "$INSTDIR\share\count-1\count-config.cmake" "$INSTDIR\count-config.cmake"
  Rename "$INSTDIR\share\count-1\count-config-version.cmake" "$INSTDIR\count-config-version.cmake"")
set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "  Delete "$INSTDIR\count-config.cmake"
  Delete "$INSTDIR\count-config-version.cmake"")
set(CPACK_NSIS_HELP_LINK "http://www.openrtm.org")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "C:\Program Files (x86)")
set(CPACK_NSIS_MENU_LINKS "C:/Program Files (x86)/Count/share/doc/count-1/html/index.html;Component documentation")
set(CPACK_NSIS_MODIFY_PATH "ON")
set(CPACK_NSIS_MUI_ICON "C:/workspace/Count/cmake\rt_middleware_logo.ico")
set(CPACK_NSIS_MUI_UNIICON "C:/workspace/Count/cmake\rt_middleware_logo.ico")
set(CPACK_NSIS_PACKAGE_NAME "Count100")
set(CPACK_NSIS_URL_INFO_ABOUT "http://www.openrtm.org")
set(CPACK_OUTPUT_CONFIG_FILE "C:/workspace/Count/build/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "C:/Program Files/CMake/share/cmake-3.12/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "")
set(CPACK_PACKAGE_EXECUTABLES "countComp;countComp")
set(CPACK_PACKAGE_FILE_NAME "Count-1.0.0-Source")
set(CPACK_PACKAGE_ICON "C:/workspace/Count/cmake\rt_middleware_logo.bmp")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Count100")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "Count100")
set(CPACK_PACKAGE_NAME "Count")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Nana Otsuka")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PROJECT_CONFIG_FILE "C:/workspace/Count/build/cpack_options.cmake")
set(CPACK_RESOURCE_FILE_LICENSE "C:/workspace/Count/cmake/License.rtf")
set(CPACK_RESOURCE_FILE_README "C:/Program Files/CMake/share/cmake-3.12/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "C:/Program Files/CMake/share/cmake-3.12/Templates/CPack.GenericWelcome.txt")
set(CPACK_RPM_PACKAGE_SOURCES "ON")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_7Z "ON")
set(CPACK_SOURCE_CYGWIN "")
set(CPACK_SOURCE_GENERATOR "7Z;ZIP")
set(CPACK_SOURCE_IGNORE_FILES "/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.swp\$;\\.#;/#")
set(CPACK_SOURCE_INSTALLED_DIRECTORIES "C:/workspace/Count;/")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "C:/workspace/Count/build/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "Count-1.0.0-Source")
set(CPACK_SOURCE_RPM "")
set(CPACK_SOURCE_TBZ2 "")
set(CPACK_SOURCE_TGZ "")
set(CPACK_SOURCE_TOPLEVEL_TAG "win32-Source")
set(CPACK_SOURCE_TXZ "")
set(CPACK_SOURCE_TZ "")
set(CPACK_SOURCE_ZIP "ON")
set(CPACK_STRIP_FILES "")
set(CPACK_SYSTEM_NAME "win32")
set(CPACK_TOPLEVEL_TAG "win32-Source")
set(CPACK_WIX_LANG "ja-jp")
set(CPACK_WIX_SIZEOF_VOID_P "4")
set(CPACK_WIX_XSL "C:/workspace/Count/build/wix.xsl")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "C:/workspace/Count/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()