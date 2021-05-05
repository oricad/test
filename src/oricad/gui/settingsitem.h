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

#ifndef INCLUDED_ORICAD_GUI_SETTINGSITEM
#define INCLUDED_ORICAD_GUI_SETTINGSITEM

#include <QVariant>
#include <QVector>

namespace oricad {
namespace gui {

class SettingsItem
{
public:
  explicit SettingsItem(
    const QVector<QVariant>& data, SettingsItem* parent = nullptr);
  ~SettingsItem();

  void appendChild(SettingsItem* child);
  SettingsItem* child(int index);
  int numChildren() const;
  int numData() const;
  QVariant data(int index) const;
  int row() const;
  SettingsItem* parent();

private:
  QVector<QVariant> _data;
  QVector<SettingsItem*> _children;
  SettingsItem* _parent;
};

}
}

#endif
