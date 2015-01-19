#include "rss_channel.h"
#include "rss_item.h"

#include <QVariant>

RssChannel::RssChannel(const QString& url)
    : AbstractListItem()
    , m_data(new RssChannelDataPrivate(url))
{
    qRegisterMetaType<RssItem>("RssChannel");
}

RssChannel::RssChannel(const RssChannel& other)
    : AbstractListItem()
    , m_data(other.m_data)
{
    qRegisterMetaType<RssItem>("RssChannel");
}

RssChannel &RssChannel::operator=(const RssChannel &other)
{
    m_data = other.m_data;
    return *this;
}

QVariant RssChannel::data(int role) const {
    switch(role) {
    case TitleRole:
        return m_data->m_title;
        break;
    case LinkRole:
        return m_data->m_link;
        break;
    case DescriptionRole:
        return m_data->m_description;
        break;
    case LastBuildDateRole:
        return m_data->m_lastBuildDate;
        break;
    case ImageSourceRole:
        return m_data->m_imageSource;
        break;
    case UrlRole:
        return m_data->m_url;
        break;
    default: return QVariant();
    }
}

QHash<int, QByteArray> RssChannel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[LinkRole] = "link";
    roles[DescriptionRole] = "description";
    roles[LastBuildDateRole] = "lastBuildDate";
    roles[ImageSourceRole] = "imageSource";
    roles[UrlRole] = "url";
    return roles;
}

QString RssChannel::id() const
{
    return m_data->m_url;
}

void RssChannel::setData(int role, const QVariant& data)
{
    switch (role) {
    case TitleRole:
        m_data->m_title = data.toString();
        break;
    case LinkRole:
        m_data->m_link = data.toString();
        break;
    case DescriptionRole:
        m_data->m_description = data.toString();
        break;
    case LastBuildDateRole:
        m_data->m_lastBuildDate = data.toString();
        break;
    case ImageSourceRole:
        m_data->m_imageSource = data.toString();
        break;
    default:
        return;
    }
}


bool RssChannel::isOkToShow() const
{
    return m_data->m_items.size() > 0;
}

void RssChannel::setTitle(const QString& title)
{
    m_data->m_title = title;
}


QString RssChannel::title() const
{
    return m_data->m_title;
}

void RssChannel::setLink(const QString &link)
{
    m_data->m_link = link;
}

QString RssChannel::link() const
{
    return m_data->m_link;
}

void RssChannel::setDescription(const QString &description)
{
    m_data->m_description = description;
}

QString RssChannel::description() const
{
    return m_data->m_description;
}

void RssChannel::setImageSource(const QString &source)
{
    m_data->m_imageSource = source;
}

QString RssChannel::imageSource() const
{
    return m_data->m_imageSource;
}

QString RssChannel::url() const
{
    return m_data->m_url;
}

QList<RssItem>& RssChannel::items()
{
    return m_data->m_items;
}

void RssChannel::addItem(const RssItem& item)
{
    m_data->m_items << item;
}

