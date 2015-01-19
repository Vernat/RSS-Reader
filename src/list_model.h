#ifndef LIST_MODEL_H
#define LIST_MODEL_H

#include <QAbstractListModel>

class AbstractListItem;

class ListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ListModel(AbstractListItem* prototype, QObject* parent = 0);
    ~ListModel();

public:
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    void appendRow(AbstractListItem* item);
    void appendRows(const QList<AbstractListItem*>& items);
    void insertRow(int row, AbstractListItem* item);
    bool removeRow(int row, const QModelIndex& parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());
    AbstractListItem* takeRow(int row);
    AbstractListItem* find(const QString& id);
    QModelIndex indexFromItem(const AbstractListItem* item) const;
    void clear();
    void remove(const QString& id);
    bool empty() const;
    void rebuildIdIndex();
    Q_INVOKABLE int getIdIndex(const QString symbol);

private slots:
    void handleItemChange();

private:
    AbstractListItem*                 m_prototype;
    QList<AbstractListItem*>          m_list;
    QHash<QString, AbstractListItem*> m_mapIdToItem;
    QHash<QString, int>               m_idIndex;
};

#endif // LIST_MODEL_H
