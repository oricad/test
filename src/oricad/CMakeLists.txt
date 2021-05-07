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

find_package(Microsoft.GSL REQUIRED)
find_package(CGAL REQUIRED)
find_package(Lager REQUIRED)
find_package(Immer REQUIRED)
#find_package(Zug REQUIRED)
find_package(Catch2 REQUIRED)
include(CTest)
include(Catch)



add_subdirectory(core)

set(qtComponents Core Widgets Qml Quick QuickControls2 Concurrent) #Quick3D
find_package(Qt5 5.12 COMPONENTS ${qtComponents} REQUIRED)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(KDDockWidgets REQUIRED)

add_subdirectory(gui)
add_subdirectory(app)
