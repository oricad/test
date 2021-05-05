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

add_library(Oricad_Core SHARED)

target_link_libraries(Oricad_Core
  PUBLIC CGAL::CGAL
  PUBLIC lager
  PUBLIC immer
  PUBLIC Microsoft.GSL::GSL
)

include(GenerateExportHeader)
generate_export_header(Oricad_Core
  EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/exports/oricad/core/export.h"
)

target_include_directories(Oricad_Core
  PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/exports"
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../.."
)

set_target_properties(Oricad_Core PROPERTIES
  VERSION ${ORICAD_VERSION}
  SOVERSION ${ORICAD_VERSION_MAJOR}
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN YES
)

add_library(Oricad::Core ALIAS Oricad_Core)

target_sources(Oricad_Core
  PUBLIC
    appdata.h
    appdata.cpp
    configuration.h
    configuration.cpp
    creasepattern.h
    creasepattern.cpp
    creasepatternemptyutil.h
    creasepatternemptyutil.cpp
    document.h
    document.cpp
    documentmanager.h
    documentmanager.cpp
    file.h
    file.cpp
    preferences.h
    preferences.cpp
    recentitems.h
    recentitems.cpp
    settings.h
    settings.cpp
)

add_subdirectory(concepts)

add_executable(Oricad_Core_DocumentManager documentmanager.t.cpp)
target_include_directories(Oricad_Core_DocumentManager PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/../.."
)
target_link_libraries(Oricad_Core_DocumentManager
  PRIVATE Catch2::Catch2WithMain
  PRIVATE Oricad::Core
)
#add_test(NAME Oricad_Core_DocumentManager COMMAND Oricad_Core_DocumentManager)

catch_discover_tests(Oricad_Core_DocumentManager)
