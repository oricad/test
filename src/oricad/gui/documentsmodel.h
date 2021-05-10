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

#ifndef INCLUDED_ORICAD_GUI_DOCUMENTSMODEL
#define INCLUDED_ORICAD_GUI_DOCUMENTSMODEL

#include <oricad/core/concepts/component.h>
#include <oricad/core/document.h>
#include <oricad/core/documentmanager.h>

#include <QAbstractListModel>

#include <immer/map.hpp>
#include <lager/context.hpp>
#include <lager/extra/qt.hpp>

namespace oricad {

namespace core {
struct Document;
struct DocumentManager;
}
namespace gui {


class DocumentItem
{
public:
  DocumentItem() = default;
  ~DocumentItem() = default;
  DocumentItem(const DocumentItem&) = default;

  DocumentItem(lager::reader<core::Document> data);

  lager::reader<core::Document> document;
};

class DocumentsModel : public QAbstractListModel
{
  Q_OBJECT
public:
  enum Roles : int
  {
    NameRole = Qt::UserRole + 1,
    DocumentRole
  };


  DocumentsModel(
    core::Component<core::DocumentManager>::Context_t context,
    lager::reader<core::DocumentManager> manager);
  ~DocumentsModel() = default;

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index, int role) const override;
  QVariant
  headerData(int section, Qt::Orientation orientation, int role) const override;
  QHash<int, QByteArray> roleNames() const override;

private:
  core::Component<core::DocumentManager>::Context_t context_;

  LAGER_QT_READER(core::DocumentManager::DocumentId, activeDocument);
  LAGER_QT_READER(core::DocumentManager::Documents, documents);
};

}
}

Q_DECLARE_METATYPE(oricad::gui::DocumentItem);

#endif
