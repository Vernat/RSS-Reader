#ifndef RSS_ITEM_H
#define RSS_ITEM_H

#include "abstract_list_item.h"

#include <QVariant>
#include <QSharedDataPointer>

class RssItemDataPrivate;


class RssItemDataPrivate : public QSharedData
{
public:
    RssItemDataPrivate()
        : m_title("")
        , m_link("")
        , m_description("")
        , m_imageSource("")
    {
    }
    RssItemDataPrivate(const RssItemDataPrivate& other)
        : QSharedData(other)
        , m_title(other.m_title)
        , m_link(other.m_link)
        , m_description(other.m_description)
        , m_imageSource(other.m_imageSource)
    {
    }

    QString      m_title;
    QString      m_link;
    QString      m_description;
    QString      m_imageSource;
};


class RssItem : public AbstractListItem
{
    Q_OBJECT

public:
    enum Roles {
        InternalIdRole = Qt::UserRole + 1,
        TitleRole,
        LinkRole,
        DescriptionRole,
        ImageSourceRole
      };

    explicit RssItem();
    RssItem(const RssItem& other);

    RssItem& operator=(const RssItem& other);

public:
    virtual QVariant data(int role) const override;

    virtual void setData(int role, const QVariant& data) override;

    virtual QHash<int, QByteArray> roleNames() const override;

    virtual QString id() const override ;

    void setTitle(const QString& title);
    QString title() const;

    void setLink(const QString& link);
    QString link() const;

    void setDescription(const QString& description);
    QString description() const;

    void setImageSource(const QString& source);
    QString imageSource() const;

    bool isCorrect();

private:
    QSharedDataPointer<RssItemDataPrivate> m_data;
};

#endif // RSS_ITEM_H
