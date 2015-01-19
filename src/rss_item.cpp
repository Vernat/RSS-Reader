#include "rss_item.h"


RssItem::RssItem()
    : AbstractListItem()
    , m_data(new RssItemDataPrivate)
{
    qRegisterMetaType<RssItem>("RssItem");
}

RssItem::RssItem(const RssItem& other)
    : AbstractListItem()
    , m_data(other.m_data)
{
    qRegisterMetaType<RssItem>("RssItem");
}

RssItem& RssItem::operator=(const RssItem& other)
{
    m_data = other.m_data;
    return *this;
}


bool RssItem::isCorrect()
{
    return !(m_data->m_title.isEmpty() &&
             m_data->m_link.isEmpty() &&
             m_data->m_description.isEmpty());
}

QVariant RssItem::data(int role) const {
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
    case ImageSourceRole:
        return m_data->m_imageSource;
        break;
    default: return QVariant();
    }
}

void RssItem::setData(int role, const QVariant& data)
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
    case ImageSourceRole:
        m_data->m_imageSource = data.toString();
        break;
    default:
        return;
    }
}


QHash<int, QByteArray> RssItem::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[LinkRole] = "link";
    roles[DescriptionRole] = "description";
    roles[ImageSourceRole] = "imageSource";
    return roles;
}

QString RssItem::id() const
{
    return m_data->m_title + m_data->m_link + m_data->m_description;

}

void RssItem::setTitle(const QString &title)
{
    m_data->m_title = title;
}

QString RssItem::title() const
{
    return m_data->m_title;
}

void RssItem::setLink(const QString &link)
{
    m_data->m_link = link;
}

QString RssItem::link() const
{
    return m_data->m_link;
}

void RssItem::setDescription(const QString &description)
{
    m_data->m_description = description;
    m_data->m_description.replace("&quot;","\"");
}

QString RssItem::description() const
{
    return m_data->m_description;
}

void RssItem::setImageSource(const QString &source)
{
    m_data->m_imageSource = source;
}

QString RssItem::imageSource() const
{
    return m_data->m_imageSource;
}

