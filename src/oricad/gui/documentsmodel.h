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
