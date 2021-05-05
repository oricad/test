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

#ifndef INCLUDED_ORICAD_GUI_RECENTITEMSMENU
#define INCLUDED_ORICAD_GUI_RECENTITEMSMENU

#include <oricad/core/concepts/attributeconcept.h>
#include <oricad/core/concepts/defaultconcept.h>
#include <oricad/core/concepts/defaultstore.h>
#include <oricad/core/concepts/generalconcept.h>
#include <oricad/core/settings.h>
#include <oricad/gui/export.h>

#include <QObject>

#include <lager/cursor.hpp>
#include <lager/event_loop/manual.hpp>
#include <lager/event_loop/qml.hpp>
#include <lager/event_loop/qt.hpp>
#include <lager/extra/qt.hpp>
#include <lager/lens.hpp>
#include <lager/store.hpp>

#include <functional>
#include <iostream>
#include <string>


namespace oricad {
namespace gui {

class ORICAD_GUI_EXPORT RecentItem : public QObject
{
  Q_OBJECT

public:
  RecentItem(lager::reader<std::string> data, QObject* parent = nullptr)
    : QObject(parent)
    , LAGER_QT(text){data.xform(
        zug::map([](auto&& x) { return QString::fromStdString(x); }))}
  {}

  LAGER_QT_READER(QString, text);
};

class ORICAD_GUI_EXPORT RecentItemsModel : public lager::event_loop_quick_item
{
  Q_OBJECT
  lager::store<
    typename core::DefaultConcept<core::Settings>::Action, core::Settings>
    store_;

public:
  RecentItemsModel(QQuickItem* parent = nullptr);
  LAGER_QT_READER(int, count);

  Q_INVOKABLE RecentItem* get(int index);
  Q_INVOKABLE void clear();
  Q_INVOKABLE void add(QString string);
  Q_INVOKABLE void changeMax(int m);
};

}
}

#endif
