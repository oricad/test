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

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
//import QtQuick3D 1.15
//import QtQuick3D.Helpers 1.0

//import Oricad 1.0

ApplicationWindow {
    visibility: "Maximized"
    title: qsTr("Minimal Qml")
    width: 800
    height: 600
    color: "pink"

    menuBar: MenuBar {
        /*Menu {
            title: qsTr("&File")
            Menu {
                id: recent
                enabled: recentItems.count !== 0
                title:  qsTr("Recent files")

                Instantiator {
                    model: recentItems.count
                    MenuItem {
                       text: recentItems.get(index).text
                    }
                    onObjectAdded: recent.insertItem(index, object)
                    onObjectRemoved: recent.removeItem(object)
                }
                MenuSeparator {}
                MenuItem {
                    text: qsTr("Clear menu");
                    action: Action {
                        onTriggered: recentItems.clear()
                    }
                }
            }
        }*/
        Menu {
            title: qsTr("&Edit")
        }
        Menu {
            title: qsTr("&Help")
        }
    }

   /* RecentItems {
        id: recentItems
    }

    Button {
        id: btnclear
        Label {
            text: "Clear"
        }
        onClicked: recentItems.clear()
    }

    TextField {
        id: myText
        anchors {
            top:btnclear.bottom
        }
    }
    Button {
        id: btnadd
        anchors {
            top: myText.bottom
        }


        Label {
            text: "Add"
        }
        onClicked: recentItems.add(myText.text)
    }
    Button {
        id: btnadd2
        anchors {
            top: btnadd.bottom
        }
        Label {
            text: "Add2"
        }
        onClicked: recentItems.add(myText.text + " Ooh!!")
    }
    Rectangle {
        id: myview
        color: "lightblue"
        height: 200
        width: 400
        anchors.top: btnadd2.bottom
        ListView {
            id: recentItemsView
            anchors {
                fill: parent
            }

            model: recentItems.count
            delegate: Rectangle {
                height: 20
                Label {
                    anchors.fill: parent
                    text: recentItems.get(index).text
                }
            }
        }
    }
    TextField {
        id: max
        anchors.top: myview.bottom
        validator: IntValidator {
            bottom: 1
            top: 10
        }
    }
    Button {
        id:btnMax
        anchors.top: max.bottom
        onClicked: recentItems.changeMax(parseInt(max.txt))
        Label {
            text: "Change max"
        }
    }*/

    /*View3D {
        id: view
        anchors.fill: parent

        environment: SceneEnvironment {
            clearColor: "skyblue"
            backgroundMode: SceneEnvironment.Color
        }

        PerspectiveCamera {
            id: camera
            position: Qt.vector3d(0, 200, 300)
            eulerRotation.x: -30
        }

        DirectionalLight {
            eulerRotation.x: -30
            eulerRotation.y: -70
        }

        AxisHelper {
        }

        WasdController {
            controlledObject: camera
        }

        Model {
            position: Qt.vector3d(0, -200, 0)
            source: "#Cylinder"
            scale: Qt.vector3d(2, 0.2, 1)
            materials: [ DefaultMaterial {
                    diffuseColor: "red"
                }
            ]
        }

        Model {
            position: Qt.vector3d(0, 150, 0)
            source: "#Sphere"

            materials: [ DefaultMaterial {
                    diffuseColor: "blue"
                }
            ]

            SequentialAnimation on y {
                loops: Animation.Infinite
                NumberAnimation {
                    duration: 3000
                    to: -150
                    from: 150
                    easing.type:Easing.InQuad
                }
                NumberAnimation {
                    duration: 3000
                    to: 150
                    from: -150
                    easing.type:Easing.OutQuad
                }
            }
        }
    }*/
}
