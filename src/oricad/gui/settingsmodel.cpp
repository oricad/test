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

#include <oricad/gui/settingsmodel.h>

namespace oricad {
namespace gui {

SettingsModel::SettingsModel(const QString& data, QObject* parent)
  : QAbstractItemModel(parent)
{
  _root = new SettingsItem({tr("Title"), tr("Summary")});

}

SettingsModel::~SettingsModel()
{
  delete _root;
}

int SettingsModel::columnCount(const QModelIndex& parent) const
{
  if (parent.isValid())
    return static_cast<SettingsItem*>(parent.internalPointer())->numData();
  return _root->numData();
}

QVariant SettingsModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (role != Qt::DisplayRole)
    return QVariant();

  SettingsItem* item = static_cast<SettingsItem*>(index.internalPointer());

  return item->data(index.column());
}

Qt::ItemFlags SettingsModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::NoItemFlags;

  return QAbstractItemModel::flags(index);
}

QVariant SettingsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    return _root->data(section);
  return QVariant();
}

QModelIndex SettingsModel::parent(const QModelIndex& index) const
{
  if (!index.isValid())
    return QModelIndex();

  SettingsItem* child = static_cast<SettingsItem*>(index.internalPointer());
  SettingsItem* parent = child->parent();

  if (parent == _root)
    return QModelIndex();

  return createIndex(parent->row(), 0, parent);
}

int SettingsModel::rowCount(const QModelIndex &parentIndex) const
{
  SettingsItem* parent;
  if (parentIndex.column() > 0)
    return 0;

  if (!parentIndex.isValid())
    parent = _root;
  else
    parent = static_cast<SettingsItem*>(index.internalPointer());
  return parent->numChildren();
}

}
}
