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

add_executable(oricad WIN32)

target_link_libraries(oricad
  PUBLIC Oricad::Gui
)

target_include_directories(oricad
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../.."
)

target_sources(oricad
  PUBLIC
    oricad.m.cpp
    resources/qml/qml.qrc
    resources/images/images.qrc
)

install(TARGETS oricad)
