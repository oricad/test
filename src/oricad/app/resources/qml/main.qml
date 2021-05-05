/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * Copyright 2021 Simon Marynissen <marynissen.simon@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.2


Item {
    Loader {
        id: mainWindowLoader
        active: false
        source: "qrc:/qml/MainWindow.qml"
        asynchronous: true
        onLoaded: {
            item.show();
            splashScreenLoader.item.visible = false;
            splashScreenLoader.source = "";
        }
    }
    Loader {
        id: splashScreenLoader
        source: "qrc:/qml/SplashWindow.qml"
        onLoaded: {
            item.visible = true
            mainWindowLoader.active = true;
        }
    }
}
