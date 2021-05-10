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

#include <oricad/gui/documentsmodel.h>

#include <lager/util.hpp>

namespace oricad {
namespace gui {

DocumentItem::DocumentItem(lager::reader<core::Document> data)
  : document{data}
{}

DocumentsModel::DocumentsModel(
  core::Component<core::DocumentManager>::Context_t context,
  lager::reader<core::DocumentManager> manager)
  : context_{context}
  , LAGER_QT(documents)(manager[&core::DocumentManager::documents])
  , LAGER_QT(activeDocument){manager[&core::DocumentManager::activeDocumentId]}
{}

int DocumentsModel::rowCount(const QModelIndex& parent) const
{
  if (parent.isValid()) {
    return 0;
  }
  return documents().size();
}

QVariant DocumentsModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid()) {
    return QVariant();
  }


  QVariant result;
  result.setValue(DocumentItem(
    LAGER_QT(documents)[index.row()][lager::lenses::or_default].make()));
  return result;
}

QVariant DocumentsModel::headerData(
  int section, Qt::Orientation orientation, int role) const
{
  return QVariant();
}

QHash<int, QByteArray> DocumentsModel::roleNames() const
{
  static const auto roles =
    QHash<int, QByteArray>{{NameRole, "name"}, {DocumentRole, "document"}};
  return roles;
}

}
}
