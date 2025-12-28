# cerfConfig.cmake
# ----------------
#
# cerf cmake module.
# This module sets the following variables in your project:
#
# ::
#
#   cerf_FOUND - true if cerf and all required components found on the system
#
#
# Available components: shared static
#
# ::
#
#   shared - search for only shared library
#   static - search for only static library
#   C - search for C library only
#   CXX - search for CXX library only
#
#
# Exported targets:
#
# ::
#
# If cerf is found, this module defines the following :prop_tgt:`IMPORTED`
# targets. Target is shared _or_ static, so, for both, use separate, not
# overlapping, installations. ::
#
#   cerf::cerf - the main cerf library with header attached.
#   cerf::cerfcpp - the C++ cerf library
#
#
# Suggested usage:
#
# ::
#
#   find_package(cerf)
#   find_package(cerf 1.17.0 EXACT CONFIG REQUIRED COMPONENTS shared C)
#
#
# The following variables can be set to guide the search for this package:
#
# ::
#
#   cerf_DIR - CMake variable, set to directory containing this Config file
#   CMAKE_PREFIX_PATH - CMake variable, set to root directory of this package
#   PATH - environment variable, set to bin directory of this package
#   CMAKE_DISABLE_FIND_PACKAGE_cerf - CMake variable, disables
#     find_package(cerf) when not REQUIRED, perhaps to force internal build


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was cerfConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

set(PN cerf)
set (_valid_components
    static
    shared
    C
    CXX
)

# check library style component
if(ON)
    set(${PN}_shared_FOUND 1)
else()
    set(${PN}_static_FOUND 1)
endif()
list(FIND ${PN}_FIND_COMPONENTS "shared" _seek_shared)
list(FIND ${PN}_FIND_COMPONENTS "static" _seek_static)

# check library language component
set(targets)
if (ON)
    set(${PN}_C_FOUND 1)
    list(APPEND targets "cerf")
endif()
if(ON)
    set(${PN}_CXX_FOUND 1)
    list(APPEND targets "cerfcpp")
endif()
list(FIND ${PN}_FIND_COMPONENTS "C" _seek_C)
list(FIND ${PN}_FIND_COMPONENTS "CXX" _seek_CXX)

check_required_components(${PN})

#-----------------------------------------------------------------------------
# Don't include targets if this file is being picked up by another
# project which has already built this as a subproject
#-----------------------------------------------------------------------------
include("${CMAKE_CURRENT_LIST_DIR}/${PN}Targets.cmake")
foreach(_target ${targets})
    if(NOT TARGET ${PN}::${_target})
        get_property(_loc TARGET ${PN}::${_target} PROPERTY LOCATION)
        get_property(_ill TARGET ${PN}::${_target} PROPERTY INTERFACE_LINK_LIBRARIES)
        get_property(_id  TARGET ${PN}::${_target} PROPERTY INCLUDE_DIRECTORIES)
        get_property(_iid TARGET ${PN}::${_target} PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
        message(STATUS "  -- cerfConfig cerf::${_target} location=${_loc} interface_link_libs=${_ill} "
            "include_dirs=${_id} interface_include_dirs=${_iid}")
    else()
        message(STATUS "  -- cerfConfig skip cerf::${_target}")
    endif()
endforeach()
