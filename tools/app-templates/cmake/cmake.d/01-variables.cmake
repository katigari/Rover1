###########################################################################
# Copyright 2015, 2016, 2017 IoT.bzh
#
# author: Fulup Ar Foll <fulup@iot.bzh>
# contrib: Romain Forlot <romain.forlot@iot.bzh>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
###########################################################################


#--------------------------------------------------------------------------
#  WARNING:
#     Do not change this cmake template
#     Customise your preferences in "./etc/config.cmake"
#--------------------------------------------------------------------------

# Get colorized message output non Windows OS. You know bash ? :)
if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

# (BUG!!!) as PKG_CONFIG_PATH does not work [should be en env variable]
set(PKG_CONFIG_USE_CMAKE_PREFIX_PATH ON CACHE BOOLEAN "Flag for using prefix path")

# Native packaging name
set(NPKG_PROJECT_NAME agl-${PROJECT_NAME})

set(CMAKE_BUILD_TYPE Debug CACHE STRING "the type of build")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMP0048 1)

# Get the os type
# Used to package .deb
if(EXISTS "/etc/os-release")
	execute_process(COMMAND grep -E "^ID(=|_LIKE=)" /etc/os-release
		OUTPUT_VARIABLE TMP_OSRELEASE
	)
	if (NOT TMP_OSRELEASE STREQUAL "")
		string(REGEX REPLACE ".*=" "" OSRELEASE ${TMP_OSRELEASE})
	else()
		set(OSRELEASE "NOT DEBIAN OS")
	endif()
	message(STATUS "OSRELEASE = ${OSRELEASE}")
else()
	set(OSRELEASE "NOT DEBIAN OS")
endif()

# Include project configuration
# ------------------------------
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES ${PROJECT_LANGUAGES})
set(PROJECT_LIBDIR "${CMAKE_SOURCE_DIR}/libs" CACHE PATH "Subpath to libraries")
set(PROJECT_RESOURCES "${CMAKE_SOURCE_DIR}/data" CACHE PATH "Subpath to data")

set(AFB_TOKEN   ""      CACHE PATH "Default AFB_TOKEN")
set(AFB_REMPORT "1234" CACHE PATH "Default AFB_TOKEN")

# Project path variables
# ----------------------

# If no install dir try to guess some smart default
if(BINDINGS_INSTALL_PREFIX)
	set(BINDINGS_INSTALL_DIR ${BINDINGS_INSTALL_PREFIX}/${PROJECT_NAME} CACHE PATH "Where the binding will be installed in your system")
else()
	set(BINDINGS_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} CACHE PATH "Where the binding will be installed in your system")
endif()

set(PKGOUT_DIR package CACHE PATH "Output directory for packages")

# Define a default package directory
if(PKG_PREFIX)
	set(PROJECT_PKG_BUILD_DIR ${PKG_PREFIX}/${PKGOUT_DIR} CACHE PATH "Application contents to be packaged")
else()
	set(PROJECT_PKG_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/${PKGOUT_DIR} CACHE PATH "Application contents to be packaged")
endif()

# Paths to templates files
set (PKG_TEMPLATE_PREFIX ${CMAKE_SOURCE_DIR}/${PROJECT_APP_TEMPLATES_DIR} CACHE PATH "Default Package Templates Directory")
set(SSH_TEMPLATE_DIR "${PKG_TEMPLATE_PREFIX}/ssh" CACHE PATH "Subpath to a directory where are stored needed files to launch on remote target to debuging purposes")
set(GDB_TEMPLATE_DIR "${PKG_TEMPLATE_PREFIX}/gdb" CACHE PATH "Subpath to a directory where are stored needed files to launch debuging server on a remote target. Use gdbserver.")
set(WGT_TEMPLATE_DIR "${PKG_TEMPLATE_PREFIX}/wgt" CACHE PATH "Subpath to a directory where are stored needed files to build widget")
if(NOT WIDGET_CONFIG_TEMPLATE)
	set(WIDGET_CONFIG_TEMPLATE ${WGT_TEMPLATE_DIR}/config.xml.in CACHE PATH "Path to widget config file template (config.xml.in)")
endif()
set(RPM_TEMPLATE_DIR "${PKG_TEMPLATE_PREFIX}/rpm" CACHE PATH "Subpath to a directory where are stored needed files to build rpm package")
set(DEB_TEMPLATE_DIR "${PKG_TEMPLATE_PREFIX}/deb" CACHE PATH "Subpath to a directory where are stored needed files to build deb package")

string(REGEX REPLACE "^(.*)/.*$" "\\1" ENTRY_POINT "${PKG_TEMPLATE_PREFIX}")
set(PROJECT_PKG_ENTRY_POINT ${ENTRY_POINT}/packaging CACHE PATH "Where package build files, like rpm.spec file or config.xml, are write.")

# Path to autobuild template
set(PROJECT_TEMPLATE_AGL_AUTOBUILD_DIR ${CMAKE_SOURCE_DIR}/conf.d/autobuild/agl CACHE PATH "Subpath to a directory where are stored autobuild script")
set(PROJECT_TEMPLATE_LINUX_AUTOBUILD_DIR ${CMAKE_SOURCE_DIR}/conf.d/autobuild/linux CACHE PATH "Subpath to a directory where are stored autobuild script")

# Archive target variables
set(ARCHIVE_OUTPUT_ARCHIVE ${PROJECT_PKG_ENTRY_POINT}/${NPKG_PROJECT_NAME}_${PROJECT_VERSION}.orig.tar)
set(ARCHIVE_OUTPUT ${ARCHIVE_OUTPUT_ARCHIVE}.gz)
set(TMP_ARCHIVE_SUBMODULE ${PROJECT_PKG_ENTRY_POINT}/${NPKG_PROJECT_NAME}-sub)
set(CMD_ARCHIVE_SUBMODULE \'git archive --verbose --prefix=${NPKG_PROJECT_NAME}-${PROJECT_VERSION}/$$path/ --format tar HEAD --output ${TMP_ARCHIVE_SUBMODULE}-$$sha1.tar\' )

if(OSRELEASE MATCHES "debian" AND NOT DEFINED ENV{SDKTARGETSYSROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
	# build deb spec file from template
	set(PACKAGING_DEB_OUTPUT_DSC       ${PROJECT_PKG_ENTRY_POINT}/${NPKG_PROJECT_NAME}.dsc)
	set(PACKAGING_DEB_OUTPUT_INSTALL   ${PROJECT_PKG_ENTRY_POINT}/debian.${NPKG_PROJECT_NAME}.install)
	set(PACKAGING_DEB_OUTPUT_CHANGELOG ${PROJECT_PKG_ENTRY_POINT}/debian.changelog)
	set(PACKAGING_DEB_OUTPUT_COMPAT    ${PROJECT_PKG_ENTRY_POINT}/debian.compat)
	set(PACKAGING_DEB_OUTPUT_CONTROL   ${PROJECT_PKG_ENTRY_POINT}/debian.control)
	set(PACKAGING_DEB_OUTPUT_RULES     ${PROJECT_PKG_ENTRY_POINT}/debian.rules)
endif()
