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
