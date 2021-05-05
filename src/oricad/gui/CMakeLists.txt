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

add_library(Oricad_Gui SHARED)

target_link_libraries(Oricad_Gui
  PUBLIC Oricad::Core
  PUBLIC Qt::Widgets
  PUBLIC Qt::Quick
  PUBLIC Qt::QuickControls2
  PUBLIC Qt::Qml
  #PUBLIC Qt::Quick3D
  PUBLIC Qt::Concurrent
)

include(GenerateExportHeader)
generate_export_header(Oricad_Gui
  EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/exports/oricad/gui/export.h"
)

target_include_directories(Oricad_Gui
  PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/exports"
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../.."
)

set_target_properties(Oricad_Gui PROPERTIES
  VERSION ${ORICAD_VERSION}
  SOVERSION ${ORICAD_VERSION_MAJOR}
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN YES
)

add_library(Oricad::Gui ALIAS Oricad_Gui)

target_sources(Oricad_Gui
  PUBLIC
    recentitemsmenu.cpp
    recentitemsmenu.h
    #settingsitem.cpp
    #settingsitem.h
    qtdocumentioservice.cpp
    qtdocumentioservice.h
    documentsmodel.cpp
    documentsmodel.h
)
