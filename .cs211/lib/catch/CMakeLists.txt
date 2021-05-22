cmake_minimum_required(VERSION 3.3)
project(Catch2
        VERSION 2020.2.0
        DESCRIPTION "A reusable main for Catch2"
        LANGUAGES CXX)

###
### MAIN LIBRARY SETUP
###

add_library(catch
        include/catch.hxx
        src/catch.cxx)

set_target_properties(catch PROPERTIES
        CXX_STANDARD            14
        CXX_STANDARD_REQUIRED   On
        CXX_EXTENSIONS          Off
        VERSION                 ${PROJECT_VERSION})

target_include_directories(catch SYSTEM INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
target_include_directories(catch PRIVATE
        include)

###
### LIBRARY INSTALLATION
###

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(config_version_cmake
        ${CMAKE_CURRENT_BINARY_DIR}/Catch2/Catch2ConfigVersion.cmake)
set(config_install_dir
        ${CMAKE_INSTALL_DATADIR}/cmake/Catch2)

install(TARGETS catch EXPORT Catch2Config
        ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY   include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT      Catch2Config
        DESTINATION ${config_install_dir})
install(FILES       ${config_version_cmake}
        DESTINATION ${config_install_dir})

export(TARGETS catch FILE Catch2Config.cmake)
write_basic_package_version_file(${config_version_cmake}
        VERSION         ${CMAKE_PROJECT_VERSION}
        COMPATIBILITY   SameMinorVersion)
