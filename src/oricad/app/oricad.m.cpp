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

static void processCommandLineOptions(const QCoreApplication& app)
{
  QCommandLineParser parser;
  // text shown by --help option
  parser.setApplicationDescription("help message");
  parser.addHelpOption();
  // not using built-in addVersionOption, because we want to show more.
  QCommandLineOption versionOption{
    {QStringLiteral("v"), QStringLiteral("version")},
    QCoreApplication::translate("cli", "Display version information")};
  QCommandLineOption licenseOption{
    QStringLiteral("license"),
    QCoreApplication::translate("cli", "Display license information")};
  parser.addOptions({versionOption, licenseOption});
  parser.process(app);

  if (parser.isSet(versionOption)) {
    // should provide more info, like which graphics backend is used
    std::cout << QCoreApplication::translate("cli", "Oricad %1")
                   .arg(QCoreApplication::applicationVersion())
                   .toStdString()
              << std::endl;
    exit(0);
  }
  if (parser.isSet(licenseOption)) {
    std::cout
      << QCoreApplication::translate("cli", "GPL 3.0 or later").toStdString()
      << std::endl;
    exit(0);
  }
  // const QStringList options = parser.optionNames();
  // const QStringList positionalArguments = parser.positionalArguments();
}


int main(int argc, char** argv)
{
  QApplication app(argc, argv, QApplication::ApplicationFlags);
  QCoreApplication::setApplicationName(QStringLiteral("Oricad"));
  QCoreApplication::setApplicationVersion("1.0");
  QCoreApplication::setOrganizationDomain(QStringLiteral("oricad.org"));
  QCoreApplication::setOrganizationName(QStringLiteral("Oricad"));

  processCommandLineOptions(app);

  QQuickStyle::setStyle("Fusion");
  QQmlApplicationEngine engine(nullptr);


  // qmlRegisterUncreatableType<oricad::gui::RecentItem>("Oricad", 1, 0,
  // "RecentItem", "");
  // qRegisterMetaType<oricad::gui::RecentItem*>("RecentItem*");
  // qmlRegisterType<oricad::gui::RecentItemsModel>("Oricad", 1, 0,
  // "RecentItems");

  engine.load(QUrl(QStringLiteral("qrc:///qml/main.qml"), QUrl::StrictMode));
  return QApplication::exec();
}
