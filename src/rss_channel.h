#ifndef RSS_CHANNEL_H
#define RSS_CHANNEL_H

#include "abstract_list_item.h"

#include <QDateTime>

class RssItem;

class RssChannelDataPrivate : public QSharedData
{
public:
    RssChannelDataPrivate(const QString& url)
        : m_url(url)
        , m_title("")
        , m_link("")
        , m_description("")
        , m_lastBuildDate("")
        , m_imageSource("")
    {
    }
    RssChannelDataPrivate(const RssChannelDataPrivate& other)
        : QSharedData(other)
        , m_url(other.m_url)
        , m_title(other.m_title)
        , m_link(other.m_link)
        , m_description(other.m_description)
        , m_lastBuildDate(other.m_lastBuildDate)
        , m_imageSource(other.m_imageSource)
        , m_items(other.m_items)
    {
    }


    QString           m_url;
    QString           m_title;
    QString           m_link;
    QString           m_description;
    QString           m_lastBuildDate;
    QString           m_imageSource;
    QList<RssItem>    m_items;
};



class RssChannel : public AbstractListItem
{
public:
    enum Roles {
        InternalIdRole = Qt::UserRole + 1,
        TitleRole,
        LinkRole,
        DescriptionRole,
        LastBuildDateRole,
        ImageSourceRole,
        UrlRole
      };


    RssChannel(const QString& url);
    RssChannel(const RssChannel& other);

    RssChannel& operator=(const RssChannel& other);

public:
    virtual QVariant data(int role) const override;

    virtual void setData(int role, const QVariant& data) override;

    virtual QHash<int, QByteArray> roleNames() const override;

    virtual QString id() const override ;

    bool isOkToShow() const;

    void setTitle(const QString& title);
    QString title() const;

    void setLink(const QString& link);
    QString link() const;

    void setDescription(const QString& description);
    QString description() const;

    void setImageSource(const QString& source);
    QString imageSource() const;

    QString url() const;

    QDateTime lastBuildDate() const;

    QList<RssItem>& items();

    void addItem(const RssItem& item);

private:
    QSharedDataPointer<RssChannelDataPrivate> m_data;
};

#endif // RSS_CHANNEL_H
