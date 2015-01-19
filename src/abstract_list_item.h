#ifndef ABSTRACT_LIST_ITEM_H
#define ABSTRACT_LIST_ITEM_H

#include <QObject>
#include <QHash>

class AbstractListItem : public QObject
{
    Q_OBJECT
public:
  AbstractListItem(QObject* parent = 0) : QObject(parent) {}
  virtual ~AbstractListItem() {}

public:
  virtual QString id() const = 0;

  virtual QVariant data(int role) const = 0;

  virtual void setData(int role, const QVariant& data) = 0;

  virtual QHash<int, QByteArray> roleNames() const = 0;

signals:
  void dataChanged();
};

#endif // ABSTRACT_LIST_ITEM_H
