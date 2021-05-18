# SPDX-License-Identifier: GPL-3.0-or-later
#
# Copyright 2021 Simon Marynissen <marynissen.simon@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.20)


file(READ VERSION ORICAD_VER)
string(STRIP "${ORICAD_VER}" ORICAD_VER)
project(ORICAD
  VERSION ${ORICAD_VER}
  DESCRIPTION "Computer-aided origami design tools"
  HOMEPAGE_URL "oricad.org"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

#include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

#set(CMAKE_CXX_CPPCHECK "cppcheck")
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")
#set(CMAKE_CXX_CPPLINT "cpplint")
#set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "iwyu")
# http://www.stablecoder.ca/2018/10/30/full-cmake-helper-suite.html

enable_testing()

include(GNUInstallDirs)
set(CMAKE_INSTALL_DOCDIR ${CMAKE_INSTALL_DATAROOTDIR}/doc/${PROJECT_NAME})

if(NOT WIN32 AND CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  set(CMAKE_INSTALL_PREFIX "/opt/oricad.org/${PROJECT_NAME}")
endif()



add_subdirectory(src/oricad)
