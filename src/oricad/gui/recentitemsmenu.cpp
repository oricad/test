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

#include <oricad/gui/recentitemsmenu.h>

namespace oricad {
namespace gui {

RecentItemsModel::RecentItemsModel(QQuickItem* parent)
  : lager::event_loop_quick_item{parent}
  , store_{core::makeDefaultStore<core::DefaultConcept<core::Settings>>(
      lager::with_qt_event_loop{std::ref(*this)})}
  , LAGER_QT(count){store_.xform(zug::map(
      [](auto&& x) { return static_cast<int>(x.recentStrings.items.size()); }))}
{}

RecentItem* RecentItemsModel::get(int index)
{
  return new RecentItem{
    store_[&core::Settings::recentStrings][&core::RecentItems::items][index]
          [lager::lenses::or_default],
    this};
}

void RecentItemsModel::clear()
{
  store_.dispatch(
    core::makeAction<&core::Settings::recentStrings>(core::ClearAction{}));
}

void RecentItemsModel::add(QString string)
{
  store_.dispatch(core::makeAction<&core::Settings::recentStrings>(
    core::AddItem{string.toStdString()}));
}

void RecentItemsModel::changeMax(int max)
{
  store_.dispatch(core::makeAction<&core::Settings::recentStrings>(
    core::ChangeMaximum{static_cast<core::RecentItems::size_t>(max)}));
}

}
}
