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

#include <QApplication>
#include <QFileSystemModel>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

//#include <oricad/gui/recentitemsmenu.h>
#include "../gui/recentitemsmenu.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv, QApplication::ApplicationFlags);

  QQuickStyle::setStyle("Fusion");
  QQmlApplicationEngine engine(nullptr);


  // qmlRegisterUncreatableType<oricad::gui::RecentItem>("Oricad", 1, 0,
  // "RecentItem", "");
  qRegisterMetaType<oricad::gui::RecentItem*>("RecentItem*");
  qmlRegisterType<oricad::gui::RecentItemsModel>("Oricad", 1, 0, "RecentItems");

  engine.load(QUrl(QStringLiteral("qrc:///qml/main.qml"), QUrl::StrictMode));
  return QApplication::exec();
}
