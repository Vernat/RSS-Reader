#include "list_model.h"
#include "abstract_list_item.h"

#include <QHash>

ListModel::ListModel(AbstractListItem* prototype, QObject* parent)
    : QAbstractListModel(parent)
    , m_prototype(prototype)
{
}


int ListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_list.size();
}

QVariant ListModel::data(const QModelIndex& index, int role) const
{
    if(index.row() < 0 || index.row() >= m_list.size()) {
        return QVariant();
    }
    return m_list.at(index.row())->data(role);
}

ListModel::~ListModel()
{
    delete m_prototype;
    clear();
}

QHash<int, QByteArray> ListModel::roleNames() const
{
    return m_prototype->roleNames();
}

void ListModel::appendRow(AbstractListItem* item)
{
    appendRows(QList<AbstractListItem*>() << item);
}

void ListModel::appendRows(const QList<AbstractListItem*> &items)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount() + items.size() - 1);

    foreach (AbstractListItem* item, items) {
        connect(item, SIGNAL(dataChanged()),
                this, SLOT(handleItemChange()));
        m_list.append(item);
        m_mapIdToItem.insert(item->id(), item);
        QString id = m_list.last()->id();
        if (!id.isEmpty()) {
            if (!m_idIndex.contains(id)) {
                m_idIndex.insert(id, m_list.size() - 1);
            }
        }
    }

    endInsertRows();
}

void ListModel::insertRow(int row, AbstractListItem* item)
{
    beginInsertRows(QModelIndex(), row, row);

    connect(item, SIGNAL(dataChanged()),
            this, SLOT(handleItemChange()));

    m_list.insert(row, item);
    m_mapIdToItem.insert(item->id(), item);
    rebuildIdIndex();

    endInsertRows();
}

void ListModel::handleItemChange()
{
    AbstractListItem* item = static_cast<AbstractListItem*>(sender());
    QModelIndex index = indexFromItem(item);
    if (index.isValid()) {
        emit dataChanged(index, index);
    }
}

AbstractListItem* ListModel::find(const QString& id)
{
    if (!m_mapIdToItem.contains(id)) {
        return nullptr;
    } else {
        return m_mapIdToItem[id];
    }
}

QModelIndex ListModel::indexFromItem(const AbstractListItem* item) const
{
    Q_ASSERT(item);
    for (int row = 0; row < m_list.size(); ++row) {
        if (m_list.at(row) == item) {
            return index(row);
        }
    }
    return QModelIndex();
}

void ListModel::clear()
{
    beginResetModel();

    m_list.clear();
    m_mapIdToItem.clear();
    m_idIndex.clear();

    endResetModel();
}

bool ListModel::removeRow(int row, const QModelIndex& parent)
{
    Q_UNUSED(parent);
    if (row < 0 || row >= m_list.size()) {
        return false;
    }
    beginRemoveRows(QModelIndex(), row, row);

    AbstractListItem* item = m_list.takeAt(row);
    m_mapIdToItem.remove(item->id());
    rebuildIdIndex();

    endRemoveRows();
    return true;
}

bool ListModel::removeRows(int row, int count, const QModelIndex& parent)
{
    Q_UNUSED(parent);
    if (row < 0 || (row + count) >= m_list.size())
        return false;
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    for (int i = 0; i < count; ++i) {
        AbstractListItem* item = m_list.takeAt(row);
        m_mapIdToItem.remove(item->id());
    }
    rebuildIdIndex();
    endRemoveRows();
    return true;
}

AbstractListItem* ListModel::takeRow(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    AbstractListItem* item = m_list.takeAt(row);
    m_mapIdToItem.remove(item->id());
    rebuildIdIndex();
    endRemoveRows();
    return item;
}

void ListModel::remove(const QString& id)
{
    if (!m_mapIdToItem.contains(id)) {
        return;
    }
    AbstractListItem* item = m_mapIdToItem[id];
    int row = m_list.indexOf(item);
    removeRow(row);
}

bool ListModel::empty() const
{
    return m_list.empty();
}

void ListModel::rebuildIdIndex()
{
    m_idIndex.clear();
    for (int i = 0; i < m_list.size(); ++i) {
        QString id = m_list[i]->id();
        if (!id.isEmpty()) {
            if (!m_idIndex.contains(id)) {
                m_idIndex.insert(id, i);
            }
        }
    }
}

int ListModel::getIdIndex(const QString id)
{
    if (m_idIndex.contains(id)) {
        return m_idIndex[id];
    } else {
        return -1;
    }
}

