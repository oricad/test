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

#include <oricad/gui/settingsitem.h>

namespace oricad {
namespace gui {

SettingsItem::SettingsItem(const QVector<QVariant>& data, SettingsItem* parent)
  : _data(data)
  , _parent(parent)
{}

SettingsItem::~SettingsItem()
{
  qDeleteAll(_children);
}

void SettingsItem::appendChild(SettingsItem* child)
{
  _children.append(child);
}

SettingsItem* SettingsItem::child(int index)
{
  if (index < 0 || index >= _children.size()) {
    return nullptr;
  }
  return _children.at(index);
}

int SettingsItem::numChildren() const
{
  return _children.count();
}

int SettingsItem::numData() const
{
  return _data.count();
}

QVariant SettingsItem::data(int index) const
{
  if (index < 0 || index >= _data.size()) {
    return QVariant();
  }
  return _data.at(index);
}

SettingsItem* SettingsItem::parent()
{
  return _parent;
}

int SettingsItem::row() const
{
  if (_parent != nullptr) {
    return _parent->_children.indexOf(const_cast<SettingsItem*>(this));
  }
  return 0;
}

}
}
