
#include "rss_news_feed_provider.h"
#include "rss_item.h"
#include "rss_channel.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QXmlStreamReader>



RssNewsFeedProvider::RssNewsFeedProvider(const QString& url, QObject* parent)
    : NewsFeedProviderInterface(parent)
    , m_url(url)
    , m_isBusy(false)
    , m_manager(new QNetworkAccessManager())
{
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this,      SLOT(onFinished(QNetworkReply*)));
}

RssNewsFeedProvider::~RssNewsFeedProvider()
{
    delete m_manager;
}

void RssNewsFeedProvider::updateFeed()
{
    if (m_isBusy) {
        return;
    }
    QUrl url = QUrl::fromPercentEncoding(QByteArray().append(m_url));
    if (url.isValid()) {
        m_manager->get(QNetworkRequest(url));
        m_isBusy = true;
    } else {
        qWarning("URL is not valid!!!");
        emitFail();
    }
}

void RssNewsFeedProvider::emitFail()
{
    RssChannel emptyChannel(m_url);
    emit gotFeed(emptyChannel);
    m_isBusy = false;
}

void RssNewsFeedProvider::onFinished(QNetworkReply* reply)
{
    const QNetworkReply::NetworkError error = reply->error();
    if (error == QNetworkReply::NoError) {
        const QByteArray data = reply->readAll();
        RssChannel channel = parseData(data);
        if (channel.isOkToShow()) {
            emit gotFeed(channel);
            m_isBusy = false;
            return;
        }
    }
    emitFail();
}

RssChannel RssNewsFeedProvider::parseData(const QByteArray& data)
{
    QXmlStreamReader reader;
    reader.addData(data);
    RssChannel channel(m_url);
    while (!reader.atEnd() && !reader.hasError() &&
           !(reader.tokenType() == QXmlStreamReader::EndElement &&
             reader.name() == "channel")) {
        QXmlStreamReader::TokenType token = reader.readNext();
        if (token == QXmlStreamReader::StartElement)
        {
            if (reader.name() == "item") {
                RssItem item = parseItem(reader);
                if (item.isCorrect()) {
                    channel.addItem(item);
                }
            } else if (reader.name() == "title") {
                reader.readNext();
                channel.setTitle(reader.text().toString());
            } else if (reader.name() == "link") {
                reader.readNext();
                channel.setLink(reader.text().toString());
            } else if (reader.name() == "description") {
                reader.readNext();
                channel.setDescription(reader.text().toString());
            } else if (reader.name() == "image") {
                const QString imageSource = parseImage(reader);
                channel.setImageSource(imageSource);
            }
        }
    }


    if (reader.error() && reader.error() != QXmlStreamReader::PrematureEndOfDocumentError) {
        qWarning() << "XML ERROR:" << reader.lineNumber() << ": " << reader.errorString();
        emitFail();
    }
    return channel;
}

RssItem RssNewsFeedProvider::parseItem(QXmlStreamReader& reader)
{
    RssItem item;
    while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "item")) {
        QXmlStreamReader::TokenType token = reader.readNext();
        if (token == QXmlStreamReader::StartElement)
        {
            if (reader.name() == "title") {
                reader.readNext();
                item.setTitle(reader.text().toString());
            } else if (reader.name() == "link") {
                reader.readNext();
                item.setLink(reader.text().toString());
            } else if (reader.name() == "description") {
                reader.readNext();
                item.setDescription(reader.text().toString());
            } else if (reader.name() == "image") {
                const QString imageSource = parseImage(reader);
                item.setImageSource(imageSource);
            }
        }
    }
    return item;
}

QString RssNewsFeedProvider::parseImage(QXmlStreamReader &reader)
{
    while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "item")) {
        QXmlStreamReader::TokenType token = reader.readNext();
        if (token == QXmlStreamReader::StartElement)
        {
            if (reader.name() == "url") {
                reader.readNext();
                return reader.text().toString();
            }
        }
    }
    return "";
}
