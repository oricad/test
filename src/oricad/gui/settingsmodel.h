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

#ifndef INCLUDED_ORICAD_GUI_SETTINGSMODEL
#define INCLUDED_ORICAD_GUI_SETTINGSMODEL

#include <oricad/gui/settingsitem.h>

#include <QAbstractItemModel>

namespace oricad {
namespace gui {

class SettingsModel : public QAbstractItemModel
{
  Q_OBJECT
public:
  explicit SettingsModel(const QString& data, QObject* parent = nullptr);
  ~SettingsModel();

  QVariant data(const QModelIndex& index, int role) const override;
  Qt::ItemFlags flags(const QModelIndex& index) const override;
  QVariant headerData(
    int section, Qt::Orientation orientation,
    int role = Qt::DisplayRole) const override;
  QModelIndex index(
    int row, int column,
    const QModelIndex& parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex& index) const override;
  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;

private:
  SettingsItem* _root;
};

}
}

#endif
