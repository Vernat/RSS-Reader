#ifndef RSS_NEWS_FEED_PROVIDER_H
#define RSS_NEWS_FEED_PROVIDER_H

#include "news_feed_provider_interface.h"
#include "rss_item.h"
#include "rss_channel.h"

#include <QNetworkReply>
#include <QXmlStreamReader>

class QNetworkAccessManager;
class RssChannel;

class RssNewsFeedProvider : public NewsFeedProviderInterface
{
public:
    RssNewsFeedProvider(const QString& url, QObject* parent = 0);
    ~RssNewsFeedProvider();

public slots:
    virtual void updateFeed() override;

protected:
    virtual void onFinished(QNetworkReply*) override;

private slots:
    void emitFail();

private:
    RssChannel parseData(const QByteArray& data);
    RssItem parseItem(QXmlStreamReader& reader);
    QString parseImage(QXmlStreamReader& reader);

private:
    const QString          m_url;
    bool                   m_isBusy;
    QNetworkAccessManager* m_manager;

private:
    friend class RssNewsProvidersTest;
};

#endif // RSS_NEWS_FEED_PROVIDER_H
